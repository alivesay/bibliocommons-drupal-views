<?php

class bibliocommons_field_text extends views_handler_field {
  
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

  // block any calls to pre_render()
  function pre_render() {}
}
