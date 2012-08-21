<?php

class bibliocommons_argument_text extends views_handler_argument {
  function default_summary($order, $by = NULL) {}
  function summary_query() {}
  function summary_name_field() {}
  function summary_basics($count_field = TRUE) {}
  function summary_sort($order, $by = NULL) {}

  function query() {
    if (isset($this->argument, $this->definition['bibliocommons']['filter_key'])) {
      $this->query->add_filter($this->table, $this->definition['bibliocommons']['filter_key'], $this->argument);
    }
  }
}
