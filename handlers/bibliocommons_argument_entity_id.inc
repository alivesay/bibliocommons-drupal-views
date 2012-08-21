<?php

class bibliocommons_argument_entity_id extends views_handler_argument {
  function default_summary($order, $by = NULL) {}
  function summary_query() {}
  function summary_name_field() {}
  function summary_basics($count_field = TRUE) {}
  function summary_sort($order, $by = NULL) {}

  function query() {
  
    $result = db_select('field_data_field_bibliocommons_list_url', 'f')
    ->fields('f', array('field_bibliocommons_list_url_value'))
    ->condition('entity_id', $this->argument,'=')
    ->execute()
    ->fetchAssoc();

      $this->query->add_filter($this->table, $this->definition['bibliocommons']['filter_key'], $result['field_bibliocommons_list_url_value']);
  }
}