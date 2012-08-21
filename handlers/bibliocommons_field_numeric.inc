<?php

class bibliocommons_field_numeric extends views_handler_field_numeric {

  function add_additional_fields($fields = NULL) {
    foreach ($fields as $field)
      $this->aliases[$field] = $this->query->add_field($this->table, $field);
  }

  function query() {
    $this->field_alias = $this->query->add_field($this->table, $this->real_field);

    if (!empty($this->additional_fields))
      $this->add_additional_fields($this->additional_fields);
  }

  function render($row) {
    return parent::render($row);
  }
}
