<?php

/**
 * @file
 * 
 * BiblioCommons Views backend.
 */

/**
 * Implements hook_views_plugin()
 */
function bibliocommons_views_plugins() {
  return array(
    'module' => 'bibliocommons',
    'query' => array(
      'bibliocommons_query' => array(
        'title'   => t('BiblioCommons API Query'),
        'help'    => t('Query the <a href="http://developer.bibliocommons.com">BiblioCommons API</a>'),
        'handler' => 'bibliocommons_views_plugin_query',
        'path'    => drupal_get_path('module', 'bibliocommons') . '/plugins',
      ),
    ),
  );
}

/**
 * Implements hook_views_data()
 */
function bibliocommons_views_data() {
  $data = array();

  // Lists
  $data['bibliocommons_lists']['table']['group'] = t('BiblioCommons Lists');
  $data['bibliocommons_lists']['table']['base'] = array(
    'query class' => 'bibliocommons_query',
    'field' => 'id',
    'title' => t('BiblioCommons Lists'), 
    'help' => t('Query recently created Lists using the BiblioCommons RESTful API.'),
  );

   $data['bibliocommons_lists']['id'] = array(
    'title'  => t('id'),
    'help'   => t('The unique list ID.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
    'filter' => array(
      'handler' => 'bibliocommons_filter_text',
      'bibliocommons' => array('filter_key' => 'id'),
    ),
  );

  $data['bibliocommons_lists']['name'] = array(
    'title'  => t('name'),
    'help'   => t('The name of the list.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
      'click sortable' => TRUE,
    ),
    'sort'   => array(
      'handler' => 'bibliocommons_sort'
    ),
  );

  $data['bibliocommons_lists']['item_count'] = array(
    'title'  => t('item_count'),
    'help'   => t('The total number of items on the list.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_numeric',
    ),
  );

  $data['bibliocommons_lists']['details_url'] = array(
    'title'  => t('details_url'),
    'help'   => t('The URL for the list details page.'),

    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_lists']['created'] = array(
    'title'  => t('created'),
    'help'   => t('The date and time that the list was created.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_lists']['updated'] = array(
    'title'  => t('updated'),
    'help'   => t('The date and time that the list was last updated.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_lists']['list_type_id'] = array(
    'title'  => t('list_type_id'),
    'help'   => t('The ID of the list type.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_lists']['list_type_name'] = array(
    'title'  => t('list_type_name'),
    'help'   => t('The user-friendly name of the list type.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_lists']['user_id'] = array(
    'title'  => t('user_id'),
    'help'   => t('The user ID.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_lists']['user_name'] = array(
    'title'  => t('user_name'),
    'help'   => t('The user\'s screen name.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_lists']['user_profile_url'] = array(
    'title'  => t('user_profile_url'),
    'help'   => t('The URL for the user\'s profile page.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );


  // List
  $data['bibliocommons_list']['table']['group'] = t('BiblioCommons List');
  $data['bibliocommons_list']['table']['base'] = array(
    'query class' => 'bibliocommons_query',
    'field' => 'id',
    'title' => t('BiblioCommons List'), 
    'help'  => t('Query a List using the BiblioCommons RESTful API.'),
  );

   $data['bibliocommons_list']['header'] = array(
     'title'  => t('List header'),
     'help'   => t('Display List information.'),
     'area'   => array(
       'handler' => 'views_handler_area_text',
     ),
   );

   $data['bibliocommons_list']['id'] = array(
    'title'  => t('id'),
    'help'   => t('The unique list ID.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
    'filter' => array(
      'handler' => 'bibliocommons_filter_text',
      'bibliocommons' => array('filter_key' => 'id'),
    ),
    'argument' => array(
      'handler' => 'bibliocommons_argument_text',
      'bibliocommons' => array('filter_key' => 'id'),
    ),
  );

  $data['bibliocommons_list']['entity_id'] = array(
    'title'  => t('Entity ID'),
    'help'   => t('The entity ID (to be use with an EVA argument).'),
    'argument' => array(
      'handler' => 'bibliocommons_argument_entity_id',
      'bibliocommons' => array('filter_key' => 'id'),
    ),
  );
  
  $data['bibliocommons_list']['name'] = array(
    'title'  => t('name'),
    'help'   => t('The name of the list.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['item_count'] = array(
    'title'  => t('item_count'),
    'help'   => t('The total number of items on the list.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['details_url'] = array(
    'title'  => t('details_url'),
    'help'   => t('The URL for the list details page.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['created'] = array(
    'title'  => t('created'),
    'help'   => t('The date and time that the list was created.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['updated'] = array(
    'title'  => t('updated'),
    'help'   => t('The date and time that the list was last updated.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['list_type_id'] = array(
    'title'  => t('list_type_id'),
    'help'   => t('The ID of the list type.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['list_type_name'] = array(
    'title'  => t('list_type_name'),
    'help'   => t('The user-friendly name of the list type.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['user_id'] = array(
    'title'  => t('user_id'),
    'help'   => t('The user ID.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['user_name'] = array(
    'title'  => t('user_name'),
    'help'   => t('The user\'s screen name.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['user_profile_url'] = array(
    'title'  => t('user_profile_url'),
    'help'   => t('The URL for the user\'s profile page.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

/*
$data['bibliocommons_list']['list_items_json'] = array(
    'title'  => t('list_items_json'),
    'help'   => t('JSON string containing list items.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );
*/
  $data['bibliocommons_list']['title_id'] = array(
    'title'  => t('title_id'),
    'help'   => t('The ID of the title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['title_title'] = array(
    'title'  => t('title_title'),
    'help'   => t('The title of the title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );
  
  $data['bibliocommons_list']['title_sub_title'] = array(
    'title'  => t('title_sub_title'),
    'help'   => t('The subtitle of the title, if one exists.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['title_format_id'] = array(
    'title'  => t('title_format_id'),
    'help'   => t('The ID of the format.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['title_format_name'] = array(
    'title'  => t('title_format_name'),
    'help'   => t('The user-friendly name of the format.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['title_details_url'] = array(
    'title'  => t('title_details_url'),
    'help'   => t('The URL for the title details page in the catalog.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_details_url',
    ),
  );

  $data['bibliocommons_list']['title_availability_id'] = array(
    'title'  => t('title_availability_id'),
    'help'   => t('The ID of the availability status of the title, across all copies and locations.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['title_availability_name'] = array(
    'title'  => t('title_availability_name'),
    'help'   => t('The user-friendly name of the availability status of the title, across all copies and locations.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['title_authors'] = array(
    'title'  => t('title_authors'),
    'help'   => t('The list of authors.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_authors',
    ),
  );

  $data['bibliocommons_list']['title_isbns'] = array(
    'title'  => t('title_isbns'),
    'help'   => t('The list of all ISBN identifiers associated with the title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['title_book_jacket'] = array(
    'title'  => t('title_book_jacket'),
    'help'   => t('The book jacket image from syndetics, if available.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_book_jacket',
    ),
  );
  
  $data['bibliocommons_list']['title_upcs'] = array(
    'title'  => t('title_upcs'),
    'help'   => t('The list of all UPC identifiers associated with the title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['title_call_number'] = array(
    'title'  => t('title_call_number'),
    'help'   => t('The call number associated with the title.  Note that the call number for some copies may be different.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['title_description'] = array(
    'title'  => t('title_description'),
    'help'   => t('A description of the title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['title_additional_contributors'] = array(
    'title'  => t('title_additional_contributors'),
    'help'   => t('The list of additional contributors.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['title_publishers'] = array(
    'title'  => t('title_publishers'),
    'help'   => t('The list of publishers.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['title_pages'] = array(
    'title'  => t('title_pages'),
    'help'   => t('The number of pages.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_numeric',
    ),
  );

  $data['bibliocommons_list']['title_series'] = array(
    'title'  => t('title_series'),
    'help'   => t('The Series information if this title is part of a series.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['title_edition'] = array(
    'title'  => t('title_edition'),
    'help'   => t('The specific edition represented by this title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['title_primary_language_name'] = array(
    'title'  => t('title_primary_language_name'),
    'help'   => t('The primary language of the title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['title_languages'] = array(
    'title'  => t('title_languages'),
    'help'   => t('The list of all languages for the title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['title_contents'] = array(
    'title'  => t('title_contents'),
    'help'   => t('The table of contents.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['title_performers'] = array(
    'title'  => t('title_performers'),
    'help'   => t('The list of performers in the title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['title_suitabilities'] = array(
    'title'  => t('title_suitabilities'),
    'help'   => t('The list of audience suitabilities.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['title_notes'] = array(
    'title'  => t('title_notes'),
    'help'   => t('The list of all notes associated with the title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['title_statement_of_responsibility'] = array(
    'title'  => t('title_statement_of_responsibility'),
    'help'   => t('The statement of responsibility.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_list']['title_physical_description'] = array(
    'title'  => t('title_physical_description'),
    'help'   => t('The physical description of the title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  // Titles
  $data['bibliocommons_titles']['table']['group'] = t('BiblioCommons Titles');
  $data['bibliocommons_titles']['table']['base'] = array(
    'query class' => 'bibliocommons_query',
    'field' => 'id',
    'title' => t('BiblioCommons Titles'), 
    'help' => t('Query for Titles using the BiblioCommons RESTful API.'),
  );

   $data['bibliocommons_titles']['id'] = array(
    'title'  => t('id'),
    'help'   => t('The title ID.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
    'filter' => array(
      'handler' => 'bibliocommons_filter_text',
      'bibliocommons' => array('filter_key' => 'id'),
    ),
  );

  $data['bibliocommons_titles']['q'] = array(
    'title'  => t('q'),
    'help'   => t('The query string to search for.'),
    'filter' => array(
      'handler' => 'bibliocommons_filter_text',
      'bibliocommons' => array('filter_key' => 'q'),
    ),
    'argument' => array(
      'handler' => 'bibliocommons_argument_text',
      'bibliocommons' => array('filter_key' => 'q'),
    ),
  );

  $data['bibliocommons_titles']['library'] = array(
    'title'  => t('library'),
    'help'   => t('The ID of the library catalog to search.'),
    'filter' => array(
      'handler' => 'bibliocommons_filter_text',
      'bibliocommons' => array('filter_key' => 'library'),
    ),
  );
 
  $data['bibliocommons_titles']['title'] = array(
    'title'  => t('title'),
    'help'   => t('The title of the title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );
  
  $data['bibliocommons_titles']['sub_title'] = array(
    'title'  => t('sub_title'),
    'help'   => t('The subtitle of the title, if one exists.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_titles']['format_id'] = array(
    'title'  => t('format_id'),
    'help'   => t('The ID of the format.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_titles']['format_name'] = array(
    'title'  => t('format_name'),
    'help'   => t('The user-friendly name of the format.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_titles']['details_url'] = array(
    'title'  => t('details_url'),
    'help'   => t('The URL for the title details page in the catalog.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_titles']['availability_id'] = array(
    'title'  => t('availability_id'),
    'help'   => t('The ID of the availability status of the title, across all copies and locations.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_titles']['availability_name'] = array(
    'title'  => t('availability_name'),
    'help'   => t('The user-friendly name of the availability status of the title, across all copies and locations.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_titles']['authors'] = array(
    'title'  => t('authors'),
    'help'   => t('The list of authors.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_titles_authors',
    ),
  );

  $data['bibliocommons_titles']['isbns'] = array(
    'title'  => t('isbns'),
    'help'   => t('The list of all ISBN identifiers associated with the title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_titles']['upcs'] = array(
    'title'  => t('upcs'),
    'help'   => t('The list of all UPC identifiers associated with the title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_titles']['call_number'] = array(
    'title'  => t('call_number'),
    'help'   => t('The call number associated with the title.  Note that the call number for some copies may be different.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_titles']['description'] = array(
    'title'  => t('description'),
    'help'   => t('A description of the title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_titles']['additional_contributors'] = array(
    'title'  => t('additional_contributors'),
    'help'   => t('The list of additional contributors.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_titles']['publishers'] = array(
    'title'  => t('publishers'),
    'help'   => t('The list of publishers.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_lists']['pages'] = array(
    'title'  => t('pages'),
    'help'   => t('The number of pages.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_numeric',
    ),
  );

  $data['bibliocommons_titles']['series'] = array(
    'title'  => t('series'),
    'help'   => t('The Series information if this title is part of a series.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_titles']['edition'] = array(
    'title'  => t('edition'),
    'help'   => t('The specific edition represented by this title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_titles']['primary_language_name'] = array(
    'title'  => t('primary_language_name'),
    'help'   => t('The primary language of the title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_titles']['languages'] = array(
    'title'  => t('languages'),
    'help'   => t('The list of all languages for the title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_titles']['contents'] = array(
    'title'  => t('contents'),
    'help'   => t('The table of contents.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_titles']['performers'] = array(
    'title'  => t('performers'),
    'help'   => t('The list of performers in the title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_titles']['suitabilities'] = array(
    'title'  => t('suitabilities'),
    'help'   => t('The list of audience suitabilities.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_titles']['notes'] = array(
    'title'  => t('notes'),
    'help'   => t('The list of all notes associated with the title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_titles']['statement_of_responsibility'] = array(
    'title'  => t('statement_of_responsibility'),
    'help'   => t('The statement of responsibility.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_titles']['physical_description'] = array(
    'title'  => t('physical_description'),
    'help'   => t('The physical description of the title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );
  
  $data['bibliocommons_titles']['title_book_jacket'] = array(
    'title'  => t('title_book_jacket'),
    'help'   => t('The book jacket image from syndetics, if available.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_book_jacket',
    ),
  );

  // Title
  $data['bibliocommons_title']['table']['group'] = t('BiblioCommons Title');
  $data['bibliocommons_title']['table']['base'] = array(
    'query class' => 'bibliocommons_query',
    'field' => 'id',
    'title' => t('BiblioCommons Title'), 
    'help' => t('Query a Title using the BiblioCommons RESTful API.'),
  );

   $data['bibliocommons_title']['id'] = array(
    'title'  => t('id'),
    'help'   => t('The title ID.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
    'filter' => array(
      'handler' => 'bibliocommons_filter_text',
      'bibliocommons' => array('filter_key' => 'id'),
    ),
  );

  $data['bibliocommons_title']['q'] = array(
    'title'  => t('q'),
    'help'   => t('The query string to search for.'),
    'filter' => array(
      'handler' => 'bibliocommons_filter_text',
      'bibliocommons' => array('filter_key' => 'q'),
    ),
  );

  $data['bibliocommons_title']['library'] = array(
    'title'  => t('library'),
    'help'   => t('The ID of the library catalog to search.'),
    'filter' => array(
      'handler' => 'bibliocommons_filter_text',
      'bibliocommons' => array('filter_key' => 'library'),
    ),
  );
 
  $data['bibliocommons_title']['title'] = array(
    'title'  => t('title'),
    'help'   => t('The title of the title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );
  
  $data['bibliocommons_title']['sub_title'] = array(
    'title'  => t('sub_title'),
    'help'   => t('The subtitle of the title, if one exists.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_title']['format_id'] = array(
    'title'  => t('format_id'),
    'help'   => t('The ID of the format.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_title']['format_name'] = array(
    'title'  => t('format_name'),
    'help'   => t('The user-friendly name of the format.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_title']['details_url'] = array(
    'title'  => t('details_url'),
    'help'   => t('The URL for the title details page in the catalog.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_title']['availability_id'] = array(
    'title'  => t('availability_id'),
    'help'   => t('The ID of the availability status of the title, across all copies and locations.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_title']['availability_name'] = array(
    'title'  => t('availability_name'),
    'help'   => t('The user-friendly name of the availability status of the title, across all copies and locations.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_title']['authors'] = array(
    'title'  => t('authors'),
    'help'   => t('The list of authors.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_title']['isbns'] = array(
    'title'  => t('isbns'),
    'help'   => t('The list of all ISBN identifiers associated with the title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  $data['bibliocommons_title']['upcs'] = array(
    'title'  => t('upcs'),
    'help'   => t('The list of all UPC identifiers associated with the title.'),
    'field'  => array(
      'handler' => 'bibliocommons_field_text',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_handlers().
 */
function bibliocommons_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'bibliocommons') . '/handlers',
    ),
    'handlers' => array(
      'bibliocommons_field_text' => array(
        'parent' => 'views_handler_field',
      ),
      'bibliocommons_field_authors' => array(
        'parent' => 'views_handler_field',
      ),
      'bibliocommons_field_titles_authors' => array(
        'parent' => 'views_handler_field',
      ),
      'bibliocommons_field_book_jacket' => array(
        'parent' => 'views_handler_field',
      ),
      'bibliocommons_field_details_url' => array(
        'parent' => 'views_handler_field',
      ),
      'bibliocommons_field_numeric' => array(
        'parent' => 'views_handler_field_numeric',
      ),
      'bibliocommons_filter_text' => array(
        'parent' => 'views_handler_filter_equality',
      ),
      'bibliocommons_argument_text' => array(
        'parent' => 'views_handler_argument',
      ),
      'bibliocommons_argument_entity_id' => array(
        'parent' => 'views_handler_argument',
      ),
    ),
  );
}
