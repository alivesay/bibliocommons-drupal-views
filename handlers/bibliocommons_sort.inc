<?php

class bibliocommons_sort extends views_handler_sort {
  function query() {
    $this->query->add_orderby($this->table, $this->real_field, $this->options['order']);
  }
}
