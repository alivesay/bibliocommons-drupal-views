<?php

class bibliocommons_filter_text extends views_handler_filter_equality {
  function operator_options() {
    return array(
      '=' => t('Is equal to'),
    );
  }

  function query() {
    if (isset($this->value, $this->definition['bibliocommons']['filter_key'], $this->value))
      $this->query->add_filter($this->table, $this->definition['bibliocommons']['filter_key'], $this->value);
  }
}
