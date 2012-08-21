<?php

/**
 * @file
 * Do stuffs with BiblioCommons APIs...
 */ 

class bibliocommonsRequest {
  const BIBLIOCOMMONS_API_DAILY_QUERY_LIMIT = 5000;
  const BIBLIOCOMMONS_API_REQUESTS_PER_SECOND_LIMIT = 2;
  const BIBLIOCOMMONS_API_URL_DEFAULT = 'https://api.bibliocommons.com/v1/';
  const BIBLIOCOMMONS_TEMP_CACHE_TIMEOUT = 300;
  const BIBLIOCOMMONS_LIBRARY = 'mylibrary';
  
  public $version = '1';

  public $api_url;

  public $api_key;

  protected static $cache = array();

  public static function factory($type) {
    switch ($type) {
      case 'lists':
        return new bibliocommonsRequestLists();
      case 'list':
        return new bibliocommonsRequestList();
      case 'titles':
        return new bibliocommonsRequestTitles();
      case 'title':
        return new bibliocommonsRequestTitle();
      default:
        watchdog('WATCHDOG_ERROR', 'BiblioCommons API error: unhandled factory type \'' . $type . '\''); 
        return NULL;
    }
  }

  public function __construct() {
    $this->api_url = variable_get('bibliocommons_api_url', bibliocommonsRequest::BIBLIOCOMMONS_API_URL_DEFAULT);
    $this->api_key = variable_get('bibliocommons_api_key', 'INVALID_KEY');
    $this->api_library = bibliocommonsRequest::BIBLIOCOMMONS_LIBRARY;
    if ($this->api_key === 'INVALID_KEY')
      watchdog('WATCHDOG_ERROR', 'BiblioCommons API error:  bibliocommons_api_key not set');
  }

 /**
  * Sets filters for API request.
  * 
  * @param $key
  *
  * @param $value.
  *
  */
  public function set_filter($key, $value) {
    $this->filters[$key] = $value;
  }

 /**
  * Query BiblioCommons REST API
  *
  * @see http://developer.bibliocommons.com
  * 
  * @return Object
  *
  */
  public function request() {
    $url = $this->url . '?api_key=' . $this->api_key;
    $url = $url . '&library=' . $this->api_library;
    
    if (!empty($this->filters))
      $url .= '&' . $this->query_string();

    if ($cache = $this->cache_get($url)) {
      $data = $cache->data;
    } else {
      $data = $this->_request($url);
      $this->cache_set($url, $data);
    }

    return $data;
  }

  /**
   * Make the API HTTP request.
   *
   * @param Assembled API URL
   *
   * @return Object
   */
  protected function _request($url) {
    $rtv = new stdClass();
    $rtv->success = FALSE;
 
    // setup request
    $headers = array('content-type' => 'application/json');

    $rtv->url = $url;
    $rtv->response = drupal_http_request($url, $headers);
    
    // process response
    switch ($rtv->response->code) {
      // good response codes
      case 200:
        $rtv->data = json_decode($rtv->response->data);
        
        if (is_null($rtv->data))
          $rtv->error = json_error_string(json_last_error());
        else
          $rtv->success = TRUE;
         
          return $rtv;
          
        break;

      // bad response codes
      case 400:
      case 403:
      case 404:
        //  get the best error code available
        $json_error = drupal_json_decode($rtv->response->data);

        if (!is_null($json_error) && array_key_exists('error', $json_error) && array_key_exists('message', $json_error['error']))
          $rtv->error = $json_error["error"]["message"];
        else if (array_key_exists('x-mashery-error-code', $rtv->response->headers))
          $rtv->error = $rtv->response->headers['x-mashery-error-code'];
        else
          $rtv->error = $rtv->response->code.' '.$rtv->response->error;
        break;
 
      default:
        $rtv->error = 'unhandled http response: '.$rtv->response->code.' '.$rtv->response->error;
        break;
    }

    if (!isset($rtv->error))
      $rtv->error = "unhandled error";

    watchdog('WATCHDOG_ERROR', 'BiblioCommons API error: ' . $rtv->error);

    return $rtv;
  }

  /**
   * Get cached API response using Drupal's cache_get().
   * 
   * @param $url
   *    Request URL.
   * @param $reset
   *    Force database retrieval if TRUE. 
   */
  protected function cache_get($url, $reset = FALSE) {
    $cid = $this->cache_id($url);

    if (!isset(bibliocommonsRequest::$cache[$cid]) || $reset) {
      bibliocommonsRequest::$cache[$cid] = cache_get($cid, 'cache_bibliocommons');
      
      // don't return old temporary caches
      if (!empty(bibliocommonsRequest::$cache[$cid]) &&
          bibliocommonsRequest::$cache[$cid]->expire === CACHE_TEMPORARY &&
          bibliocommonsRequest::$cache[$cid]->created > (REQUEST_TIME + bibliocommonsRequest::BIBLIOCOMMONS_TEMP_CACHE_TIMEOUT))
        return FALSE;
    }

    return bibliocommonsRequest::$cache[$cid];
  }

  /**
   * Cache API response using Drupal's cache_set().
   *
   * @param $url
   *    Request URL.
   * @param $response
   *    Response to store in cache.
   */
  protected function cache_set($url, $data) {
    if ($data === FALSE) {
      cache_set($this->cache_id($url), FALSE, 'cache_bibliocommons', CACHE_TEMPORARY);}
    else
      cache_set($this->cache_id($url), $data, 'cache_bibliocommons');
  }

  /**
   * Generate unique cache ID.
   * 
   * @param $url
   *    Request URL.
   */
  protected function cache_id($url) {
    return get_class($this) . ':' . md5($url);
  }

  /**
   * Build parameter query string.
   *
   * @return string
   */
  protected function query_string() {
    if (!empty($this->filters)) {
      $filters = array();
      foreach ($this->filters as $key => $value)
        $filters[] = $key . '=' . urlencode($value);
      
      return implode('&', $filters);
    }
  }

  /**
   * Return string for json_decode error.
   * 
   * @param $errnum
   *   The json_decode error number
   */
  protected function json_error_string($errnum) {
    switch ($errnum) {
      case JSON_ERROR_NONE:
        return "JSON_ERROR_NONE";
      case JSON_ERROR_DEPTH:
        return "JSON_ERROR_DEPTH";
      case JSON_ERROR_STATE_MISMATCH:
        return "JSON_ERROR_STATE_MISMATCH";
      case JSON_ERROR_CTRL_CHAR:
        return "JSON_ERROR_CTRL_CHAR";
      case JSON_ERROR_SYNTAX:
        return "JSON_ERROR_SYNTAX";
      case JSON_ERROR_UTF8:
        return "JSON_ERROR_UTF8";
      default:
       return "UNKNOWN JSON ERROR";
    }
  }
}

/**
 * @see http://developer.bibliocommons.com/docs/lists
 *      Note:  Vendor API currently only support recently created lists.
 * 
 */
class bibliocommonsRequestLists extends bibliocommonsRequest {
 
  const MAX_REQUEST_DEPTH = 10;

  /**
   * Overrides request()
   */
  public function request() {
    $responses = array();

    $this->url = $this->api_url . 'lists';
   
    $responses[] = parent::request($this->url);

    if (!end($responses)->success)
      return NULL;
    
    // more available?
    while (end($responses)->data->page < end($responses)->data->pages && end($responses)->data->page < bibliocommonsRequestLists::MAX_REQUEST_DEPTH) {
      $this->set_filter('page', end($responses)->data->page + 1);
      $responses[] = parent::request($this->url);  
    }

    // merge responses
    return call_user_func_array('array_merge', array_map(function (&$v) { return $v->data->lists; }, $responses));
  }
}

/**
 * 
 * @see http://developer.bibliocommons.com/docs/lists_id
 * 
 */
class bibliocommonsRequestList extends bibliocommonsRequest {
 
  /**
   * Overrides request()
   */
  public function request() {

    if (!isset($this->filters['id'])) {
      watchdog('WATCHDOG_ERROR', 'BiblioCommons API error: missing required parameter \'id\'');
      return NULL;
    }
    
    $this->url = $this->api_url . 'lists/' . $this->filters['id'];
    unset($this->filters['id']);
   
    $response = parent::request($this->url);

    if (!$response->success)
      return NULL;

    //$response->data->list->list_items = json_encode($response->data->list->list_items);

    // store metadata in first row of list_items
    array_unshift(
      $response->data->list->list_items,
    
      (object)array_intersect_key(
        (array)$response->data->list, 
        array_flip(array_filter(array_keys((array)$response->data->list), function (&$v) { return $v !== 'list_items'; }))
      )
    );

    // trim the metadata for now
    array_shift($response->data->list->list_items);
    return $response->data->list->list_items;
  }
}

/**
 * @see http://developer.bibliocommons.com/docs/titles
 * 
 */
class bibliocommonsRequestTitles extends bibliocommonsRequest { 

  const MAX_REQUEST_DEPTH = 10;

  /**
   * Overrides request()
   */
  public function request() {  
    $responses = array();

    $this->url = $this->api_url . 'titles'; 
   
    $responses[] = parent::request($this->url);
   
    if (!end($responses)->success)
      return NULL;

    // more available?
//    while (end($responses)->data->page < end($responses)->data->pages && end($responses)->data->page < bibliocommonsRequestTitles::MAX_REQUEST_DEPTH) {
//      $this->set_filter('page', end($responses)->data->page + 1);
//      $responses[] = parent::request($this->url);
//    }
 
    return call_user_func_array('array_merge', array_map(function (&$r) {
      array_walk($r->data->titles, function (&$t) {
        // authors as json
        if (isset($t->authors) && !empty($t->authors))
          $t->authors = json_encode($t->authors);
      });

      return $r->data->titles;
    }, $responses));
  }
}

/**
 * @see http://developer.bibliocommons.com/docs/titles_id
 * 
 */
class bibliocommonsRequestTitle extends bibliocommonsRequest {
 
  /**
   * Overrides request()
   */
  public function request() {

    if (!isset($this->filters['id'])) {
      watchdog('WATCHDOG_ERROR', 'BiblioCommons API error: missing required parameter \'id\'');
      return NULL;
    }

    $this->url = $this->api_url . 'titles/' . $this->filters['id'];
    unset($this->filters['id']);
   
    $response = parent::request($this->url);

    if ($response->success)
      return NULL;

    if (isset($response->data->title->authors) && !empty($response->data->title->authors))
      $response->data->title->authors = json_encode($response->data->title->authors);

    return array($response->data->title);
  }
}
