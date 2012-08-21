<?php

class bibliocommons_relationship extends views_handler_relationship {
  
  function query() {
    $left_table = $this->table;
    $left_field = $this->field;

    $right_table = $this->definition['base'];
    
    // determine base table added by relationsihp
    $table_data = views_fetch_data($this->definition['base']);

    $right_field = empty($this->definition['base field']) ? $table_data['table']['base']['field'] : $this->definition['base field'];

    $this->query->add_relationship($left_table, $left_field, $right_table, $right_field);
  }
}
