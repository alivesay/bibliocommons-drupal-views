<?php

/**
 * Implements hook_views_default_views().
 */
function bibliocommons_views_default_views() {
  // Lists
  $view = new view;
  $view->name = 'bibliocommons_lists';
  $view->description = 'BiblioCommons Lists';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'bibliocommons_lists';
  $view->is_cacheable = FALSE;
  $view->disabled = FALSE;
  $view->api_version = '3.0-alpha1';
  $view->core = 7;

  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name'        => 'name',
    'item_count'  => 'item_count',
    'user_name'   => 'user_name',
    'details_url' => 'details_url',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'align'     => '',
      'seperator' => '',
    ),
   'item_count' => array(
      'align'     => '',
      'seperator' => '',
    ),
    'user_name' => array(
      'align'     => '',
      'seperator' => '',
    ),
    'details_url' => array(
      'align'     => '',
      'seperator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;

  // Lists:name
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'bibliocommons_lists';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = 'Name';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  // Lists:item_count
  $handler->display->display_options['fields']['item_count']['id'] = 'item_count';
  $handler->display->display_options['fields']['item_count']['table'] = 'bibliocommons_lists';
  $handler->display->display_options['fields']['item_count']['field'] = 'item_count';
  $handler->display->display_options['fields']['item_count']['label'] = 'Item Count';
  $handler->display->display_options['fields']['item_count']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['item_count']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['item_count']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['item_count']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['item_count']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['item_count']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['item_count']['alter']['html'] = 0;
  $handler->display->display_options['fields']['item_count']['hide_empty'] = 0;
  $handler->display->display_options['fields']['item_count']['empty_zero'] = 0;
  // Lists:user_name
  $handler->display->display_options['fields']['user_name']['id'] = 'user_name';
  $handler->display->display_options['fields']['user_name']['table'] = 'bibliocommons_lists';
  $handler->display->display_options['fields']['user_name']['field'] = 'user_name';
  $handler->display->display_options['fields']['user_name']['label'] = 'Username';
  $handler->display->display_options['fields']['user_name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['user_name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['user_name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['user_name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['user_name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['user_name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['user_name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['user_name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['user_name']['empty_zero'] = 0;
  // Lists:details_url
  $handler->display->display_options['fields']['details_url']['id'] = 'user_name';
  $handler->display->display_options['fields']['details_url']['table'] = 'bibliocommons_lists';
  $handler->display->display_options['fields']['details_url']['field'] = 'details_url';
  $handler->display->display_options['fields']['details_url']['label'] = 'Details URL';
  $handler->display->display_options['fields']['details_url']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['details_url']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['details_url']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['details_url']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['details_url']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['details_url']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['details_url']['alter']['html'] = 0;
  $handler->display->display_options['fields']['details_url']['hide_empty'] = 0;
  $handler->display->display_options['fields']['details_url']['empty_zero'] = 0;

  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'bibliocommons/lists';
  $views[$view->name] = $view;

  return $views;
}
