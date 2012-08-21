<?php

function _bibliocommons_field_view_image_style_options() {

  $options = array();
  foreach (image_styles() as $name => $style) {
    $options[$name] = $style['name'];
  }
  return $options;
}

class bibliocommons_field_book_jacket extends views_handler_field {
  
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

    $style = $this->options['image_style'];
    $syndetics_size = $this->options['syndetics_size'];
      
    if(isset($values->bibliocommons_list_title_isbns)) {
      $isbns = drupal_json_decode($values->bibliocommons_list_title_isbns);
    } 
    if(isset($values->bibliocommons_titles_isbns)) {
      $isbns = drupal_json_decode($values->bibliocommons_titles_isbns);
    }
      
    if(isset($isbns[0])) { 
      return '<img src="http://www.syndetics.com/index.aspx?isbn=' . $isbns[0] . '/' . $syndetics_size . '.gif&client=multp&type=hwwesterkid">';
    }  

    if(!isset($isbns[0])) {
      foreach ($values as $key => $value) {  
        if (substr($key, -11) == "format_name") { 
          $local_path = variable_get('bibliocommons_no_image_' . strtolower($value), '');
          if(!empty($local_path)) {
            return(theme('image_style', array('style_name' => $style, 'path' => $local_path,)));
          } else {
            $other_path = variable_get('bibliocommons_no_image_other', '');
            if(!empty($other_path)) {
              return(theme('image_style', array('style_name' => $style, 'path' => $other_path,)));
            } else {
              return '<img src="http://www.syndetics.com/index.aspx?isbn=-1/' . $syndetics_size . '.gif&client=multp&type=hwwesterkid">';
            }
          }
        }
      }  
    }
  }
  
  // block any calls to pre_render()
  function pre_render() {}
  
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $image_styles = array();
    $image_styles = _bibliocommons_field_view_image_style_options();

    $form['image_style'] = array(
      '#type' => 'select',
      '#title' => t('Image style for missing images placeholders'),
      '#options' => $image_styles,
      '#default_value' => $this->options['image_style'],
    );
    $form['syndetics_size'] = array(
      '#type' => 'select',
      '#title' => t('Image size for syndetics images'),
      '#options' => array('SC' => 'Small', 'MC' => 'Medium', 'LC' => 'Large'),
      '#default_value' => $this->options['syndetics_size'],
    );
  }
  
  function option_definition() {
    $options = parent::option_definition();
    $options['image_style'] = array('default' => 'medium');
    $options['syndetics_size'] = array('default' => 'Small');
    return $options;
  }
}