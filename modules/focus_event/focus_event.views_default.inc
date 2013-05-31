<?php
/**
 * @file
 * @todo
 */

/**
 * Implements hook_views_default_views()
 */
function focus_event_views_default_views() {
    // Start event calendar view
    $view = new view();
    $view->name = 'focus_event_calendar';
    $view->description = '';
    $view->tag = 'Calendar';
    $view->base_table = 'node';
    $view->human_name = 'Event Calendar';
    $view->core = 7;
    $view->api_version = '3.0';
    $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
    
    /* Display: Master */
    $handler = $view->new_display('default', 'Master', 'default');
    $handler->display->display_options['use_more_always'] = FALSE;
    $handler->display->display_options['link_display'] = 'page_1';
    $handler->display->display_options['access']['type'] = 'perm';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['query']['options']['query_comment'] = FALSE;
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'date_views_pager';
    $handler->display->display_options['pager']['options']['date_id'] = 'month';
    $handler->display->display_options['style_plugin'] = 'calendar_style';
    $handler->display->display_options['style_options']['name_size'] = '3';
    $handler->display->display_options['style_options']['with_weekno'] = '0';
    $handler->display->display_options['style_options']['multiday_theme'] = '1';
    $handler->display->display_options['style_options']['theme_style'] = '1';
    $handler->display->display_options['style_options']['max_items'] = '0';
    $handler->display->display_options['row_plugin'] = 'calendar_entity';
    /* Field: Content: Title */
    $handler->display->display_options['fields']['title']['id'] = 'title';
    $handler->display->display_options['fields']['title']['table'] = 'node';
    $handler->display->display_options['fields']['title']['field'] = 'title';
    $handler->display->display_options['fields']['title']['label'] = '';
    $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
    $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
    $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
    /* Field: Content: Event Date */
    $handler->display->display_options['fields']['field_focus_calendar_date']['id'] = 'field_focus_calendar_date';
    $handler->display->display_options['fields']['field_focus_calendar_date']['table'] = 'field_data_field_focus_calendar_date';
    $handler->display->display_options['fields']['field_focus_calendar_date']['field'] = 'field_focus_calendar_date';
    $handler->display->display_options['fields']['field_focus_calendar_date']['label'] = '';
    $handler->display->display_options['fields']['field_focus_calendar_date']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['field_focus_calendar_date']['hide_alter_empty'] = FALSE;
    $handler->display->display_options['fields']['field_focus_calendar_date']['settings'] = array(
      'format_type' => 'short',
      'fromto' => 'both',
      'multiple_number' => '',
      'multiple_from' => '',
      'multiple_to' => '',
      'show_repeat_rule' => '',
    );
    $handler->display->display_options['fields']['field_focus_calendar_date']['group_rows'] = FALSE;
    $handler->display->display_options['fields']['field_focus_calendar_date']['delta_offset'] = '0';
    /* Sort criterion: Content: Event Date -  start date (field_focus_calendar_date) */
    $handler->display->display_options['sorts']['field_focus_calendar_date_value']['id'] = 'field_focus_calendar_date_value';
    $handler->display->display_options['sorts']['field_focus_calendar_date_value']['table'] = 'field_data_field_focus_calendar_date';
    $handler->display->display_options['sorts']['field_focus_calendar_date_value']['field'] = 'field_focus_calendar_date_value';
    /* Filter criterion: Content: Published */
    $handler->display->display_options['filters']['status']['id'] = 'status';
    $handler->display->display_options['filters']['status']['table'] = 'node';
    $handler->display->display_options['filters']['status']['field'] = 'status';
    $handler->display->display_options['filters']['status']['value'] = 1;
    $handler->display->display_options['filters']['status']['group'] = 0;
    $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
    
    /* Display: Full */
    $handler = $view->new_display('block', 'Full', 'full');
    $handler->display->display_options['defaults']['use_ajax'] = FALSE;
    $handler->display->display_options['use_ajax'] = TRUE;
    $handler->display->display_options['defaults']['pager'] = FALSE;
    $handler->display->display_options['pager']['type'] = 'date_views_pager';
    $handler->display->display_options['pager']['options']['date_id'] = 'mini';
    $handler->display->display_options['defaults']['style_plugin'] = FALSE;
    $handler->display->display_options['style_plugin'] = 'calendar_style';
    $handler->display->display_options['style_options']['name_size'] = '1';
    $handler->display->display_options['style_options']['mini'] = '0';
    $handler->display->display_options['style_options']['with_weekno'] = '0';
    $handler->display->display_options['style_options']['multiday_theme'] = '1';
    $handler->display->display_options['style_options']['theme_style'] = '1';
    $handler->display->display_options['style_options']['max_items'] = '0';
    $handler->display->display_options['defaults']['style_options'] = FALSE;
    $handler->display->display_options['defaults']['row_plugin'] = FALSE;
    $handler->display->display_options['row_plugin'] = 'calendar_entity';
    $handler->display->display_options['row_options']['hide_empty'] = TRUE;
    $handler->display->display_options['row_options']['colors']['calendar_colors_type'] = array(
      'focus_article' => '#ffffff',
      'focus_event' => '#ffffff',
      'focus_news' => '#ffffff',
      'focus_page' => '#ffffff',
      'focus_section' => '#ffffff',
      'focus_sidebar' => '#ffffff',
      'webform' => '#ffffff',
    );
    $handler->display->display_options['defaults']['row_options'] = FALSE;
    $handler->display->display_options['defaults']['arguments'] = FALSE;
    /* Contextual filter: Date: Date (node) */
    $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
    $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
    $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
    $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
    $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
    $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
      'field_data_field_focus_calendar_date.field_focus_calendar_date_value' => 'field_data_field_focus_calendar_date.field_focus_calendar_date_value',
    );
    $handler->display->display_options['block_description'] = 'Event Calendar: Full';

    
    // Add event calendar view
    $views[$view->name] = $view;
    
    return $views;
}
