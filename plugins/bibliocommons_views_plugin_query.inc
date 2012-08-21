<?php

/**
 * @file 
 * 
 * Views backend plugin to allow querying the BiblioCommons API through the Views query interface.
 *
 * Based heavily on the <a href="http://drupal.org/project/wbapi">World Bank API</a>.
 * 
 * @see http://drupalcode.org/project/wbapi.git
 * @see http://api.drupal.org/api/views/plugins!views_plugin_query_default.inc/class/views_plugin_query_default/7
 */

class bibliocommons_views_plugin_query extends views_plugin_query {

  // Array containing API requests for this instance.
  public $requests;

  // Array mapping table aliases and field names to field aliases.
  public $aliases;

  // Array mapping left-side table/fields to right-side table/fields.
  public $joins;

  // Array of orderby clauses.
  public $orderby;

  // Array of fields required in the result set.  Rows with empty required fields are dropped prior to paging.
  public $required_fields;

  /**
   * Constructor; Create the basic query object and fill with default values.
   */
  public function init($base_table, $base_field, $options) {
    parent::init($base_table, $base_field, $options);
    module_load_include('inc', 'bibliocommons', 'bibliocommons.api');
 
    $this->requests = array();
    $this->aliases = array();
    $this->joins = array();
    $this->orderby = array();
    $this->ensure_table = array();
    $this->required_fields = array();

    $this->ensure_table($base_table);
  }

  /**
   * Implements add_relationship().
   * 
   * http://api.drupal.org/api/views/plugins%21views_plugin_query_default.inc/function/views_plugin_query_default%3A%3Aadd_relationship/7
   */
  public function add_relationship($left_table, $left_field, $right_table, $right_field) {
    if (isset($this->requests[$left_table])) {
      $this->ensure_table($right_table);
      $this->add_field($left_table, $left_field);
      $this->joins[$left_table][$left_field] = array(
        'table' => $right_table,
        'field' => $right_field,
      );
    }

    return FALSE;
  }

  /**
   * Implements add_field().
   * 
   * @see http://api.drupal.org/api/views/plugins%21views_plugin_query_default.inc/function/views_plugin_query_default%3A%3Aadd_field/7
   */
  public function add_field($table, $field, $required = FALSE) {
    $this->ensure_table($table);
    $alias = "{$table}_{$field}";
    $this->aliases[$table][$field] = $alias;
    
    if ($required)
      $this->required_fields[$alias] = $alias;

    return $alias;
  }

  /**
   * Implements add_orderby().
   *
   * @see http://api.drupal.org/api/views/plugins%21views_plugin_query_default.inc/function/views_plugin_query_default%3A%3Aadd_orderby/7
   */
  public function add_orderby($table, $field, $order) {
    $alias = $this->add_field($table, $field);
    $this->orderby = array(
      'field_alias' => $alias,
      'order' => $order,
    );
  }

  /**
   * Implements ensure_table().
   *
   * http://api.drupal.org/api/views/plugins%21views_plugin_query_default.inc/function/views_plugin_query_default%3A%3Aensure_table/7
   */
  public function ensure_table($table) {
    if (!isset($this->requests[$table])) {
      $this->requests[$table] = bibliocommonsRequest::factory($this->get_method($table));
    }
  }

  /**
   *  Returns API method name from Views table name.
   */
  protected function get_method($table) {
    return substr(strchr($table, '_'), 1);
  }
 
  /**
   * Implements add_where().
   *
   * @see http://api.drupal.org/api/views/plugins%21views_plugin_query_default.inc/function/views_plugin_query_default%3A%3Aadd_where/7
   */
  public function add_where($group, $field, $value = NULL, $operator = NULL) {
    // set '', 0, and NULL as 0
    if (empty($group)) 
      $group = 0;

    if (!isset($this->where[$group]))
      $this->set_where_group('AND', $group);

    $this->where[$group]['conditions'][] = array(
      'field' => $field, 
      'value' => $value, 
      'operator' => $operator,
    );
  }

  /**
   * Implements add_filter().
   * 
   * @see http://api.drupal.org/api/views/includes!handlers.inc/function/views_many_to_one_helper%3A%3Aadd_filter/7
   */
  public function add_filter($table, $field, $value) {
    $this->ensure_table($table);
    $this->requests[$table]->set_filter($field, $value);
  }

  /**
   * Executes subqueries as joins and provides internal query result caching.
   */
  protected function subrequest($table, $field, $arg, $base_row) {
    static $cache;

    // setup query-local cache
    $cache = !isset($cache) ? array() : $cache;

    if (isset($cache[$table][$field][$arg])) {
      $base_row = array_merge($base_row, $cache[$table][$field][$arg]);

    } elseif (!empty($this->aliases[$table])) {
      $cache[$table][$field][$arg] = array();

      // set request filter
      $request = clone $this->requests[$table];
      $request->set_filter($field, $arg);

      if ($result = $request->request()) {
        $row = array_shift($result);
        foreach ($this->aliases[$table] as $f => $alias) {
          // cache row values
          $cache[$table][$field][$arg][$alias] =
            $base_row[$alias] = isset($row->{$f}) && !is_object($row->{$f}) ? $row->{$f} : NULL;

          // execute any joins
          if (isset($this->joins[$table][$f])) {
            $sub_table = $this->joins[$table][$f]['table'];
            $sub_field = $this->joins[$table][$f]['field'];
            $sub_arg = $row->{$f};
            $base_row = $this->subrequest($sub_table, $sub_field, $sub_arg, $base_row);
          }
        }
      }

      unset($request);
    }
    return $base_row;
  }

  /**
   * Makes BiblioCommons API requests and flattens response to support Views result set.
   */
  protected function request(&$view, $table, $request) {   
    if (!empty($this->aliases[$table]) && $result = $request->request()) {

      // trim results that are not media
      $count = 0;
      $formats = explode_trim(variable_get('bibliocommons_allowed_formats', ''));
       
      foreach($result as $r) {
        if(isset($r->title->format)) {
          if(!in_array($r->title->format->name, $formats)) {
            unset($result[$count]);
          }
        } elseif(isset($r->format)) {
          if(!in_array($r->format->name, $formats)) {
            unset($result[$count]);
          }
        } else {
          unset($result[$count]);
        }
        $count++;
      }
 
      // might need to rewrite this as a recursive function if more depth is ever required...
      foreach (array_values($result) as $num => $row) { 
        foreach ($row as $i => $v) { 
          if (is_array($v)) {
            // return arrays as JSON
            $row->{$i} = json_encode($v);
          } elseif (is_object($v)) {
            // convert object properties to variables (ie., object.property to object_property)
            foreach (get_object_vars($v) as $key => $val)
              if (is_array($val))
                $row->{$i . '_' . $key} = json_encode($val);
              elseif (is_object($val))
                foreach (get_object_vars($val) as $skey => $sval) 
                  $row->{$i . '_' . $key . '_' . $skey} = $sval;
              else
                $row->{$i . '_' . $key} = $val;
          } 
        }
         
        $view->result[$num] = new stdClass;
        foreach ($this->aliases[$table] as $field => $alias) {
          // Populate field values using aliases.
          $view->result[$num]->{$alias} = isset($row->{$field}) && !is_object($row->{$field}) ? $row->{$field} : NULL;
      
          // Execute sub queries.
          if (isset($this->joins[$table][$field])) {
            $sub_table = $this->joins[$table][$field]['table'];
            $sub_field = $this->joins[$table][$field]['field'];
            $sub_arg = $row->{$field};
            // Transition to arrays for subrequests for speed.
            // Transition back to object once we're done.
            $view->result[$num] = (object) $this->subrequest($sub_table, $sub_field, $sub_arg, (array) $view->result[$num]);
          }
        }
      }
    }
  }

  /**
   * Implements execute().
   *
   * @see http://api.drupal.org/api/views/plugins%21views_plugin_query_default.inc/function/views_plugin_query_default%3A%3Aexecute/7
   */
  function execute(&$view) {
    // views 3.x-alpha3 and prior
    if (method_exists($this, 'init_pager')) 
      $this->init_pager($view);
    // views 3.x dev
    elseif (method_exists($view, 'init_pager')) 
      $view->init_pager();

    if ($this->pager->use_pager()) {
      $this->pager->set_current_page($view->current_page);
    }
    $this->pager->query();

    // make the actual request
    $view->result = array();
    $queue = $this->requests;

    $request = reset($this->requests);
    $table = key($this->requests);
    $this->request($view, $table, $request);

    // remove rows without required fields
    if (!empty($this->required_fields))
      foreach ($this->required_fields as $alias)
        foreach ($view->result as $num => $row)
          if (empty($row->{$alias}))
            unset($view->result[$num]);

    // slice the resultset
    if (isset($this->offset, $this->limit)) {
      $end = $this->offset + $this->limit;
      $end = count($view->result) >= $end ? $end : count($view->result);
      $view->result = array_slice($view->result, $this->offset, $end);
    }
  }

  /**
   * Implements placeholder().
   */
  function placeholder($base = 'views') {
    static $placeholders = array();
    if (!isset($placeholders[$base])) {
      $placeholders[$base] = 0;
      return ':' . $base;
    }
    else {
      return ':' . $base . ++$placeholders[$base];
    }
  }
}

function explode_trim($str, $delimiter = ',') {
    if ( is_string($delimiter) ) {
        $str = trim(preg_replace('|\\s*(?:' . preg_quote($delimiter) . ')\\s*|', $delimiter, $str));
        return explode($delimiter, $str);
    }
    return $str;
} 