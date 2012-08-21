<?php

class bibliocommons_field_titles_authors extends views_handler_field {
  
  function add_additional_fields($fields = NULL) {
    foreach ($fields as $field)
      $this->aliases[$field] = $this->query->add_field($this->table, $field);
  }

  function click_sort($order) {
    $this->query->add_orderby($this->table, $this->real_field, $order);
  }

  function query() {
    $this->field_alias = $this->query->add_field($this->table, $this->real_field);

    if (!empty($this->additional_fields))
      $this->add_additional_fields($this->additional_fields);
  }

  function render($values) {
    $authors = drupal_json_decode($values->bibliocommons_titles_authors);
    $authors_array = array();
    foreach($authors as $key => $value) {
      $authors_array[] = '<a href="http://mylibrary.bibliocommons.com/search?q=' . $value['name'] . '&search_category=author&t=author">' . $value['name'] . '</a>';
    }
    return implode($this->options['authors_delimiter'], $authors_array);
  }
  
  // block any calls to pre_render()
  function pre_render() {}
  
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['authors_delimiter'] = array(
      '#title' => t('String to delimit authors'),
      '#type' => 'textfield',
      '#default_value' => $this->options['authors_delimiter'],
    );
  }
  
  function option_definition() {
    $options = parent::option_definition();
    $options['authors_delimiter'] = array('default' => ' | ');
    return $options;
  }
  
}
