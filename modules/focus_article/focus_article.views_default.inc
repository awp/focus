<?php
/**
 * @file
 * @todo
 */

/**
 * Implements hook_views_default_views()
 */
function focus_article_views_default_views() {
    // Sequential Articles Views.
    $view = new view();
    $view->name = 'sequential_articles';
    $view->description = 'Contains two blocks that display the next and previous articles by date in relation to the current article viewed.';
    $view->tag = 'default';
    $view->base_table = 'node';
    $view->human_name = 'Sequential Articles';
    $view->core = 7;
    $view->api_version = '3.0';
    $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */
    
    /* Display: Master */
    $handler = $view->new_display('default', 'Master', 'default');
    $handler->display->display_options['title'] = 'Next Article';
    $handler->display->display_options['use_more_always'] = FALSE;
    $handler->display->display_options['access']['type'] = 'perm';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'some';
    $handler->display->display_options['pager']['options']['items_per_page'] = '1';
    $handler->display->display_options['style_plugin'] = 'list';
    $handler->display->display_options['style_options']['grouping'] = array(
      0 => array(
        'field' => '',
        'rendered' => 1,
        'rendered_strip' => 0,
      ),
    );
    $handler->display->display_options['row_plugin'] = 'fields';
    /* Field: Content: Title */
    $handler->display->display_options['fields']['title']['id'] = 'title';
    $handler->display->display_options['fields']['title']['table'] = 'node';
    $handler->display->display_options['fields']['title']['field'] = 'title';
    $handler->display->display_options['fields']['title']['label'] = '';
    $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
    $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
    /* Sort criterion: Content: Date (field_focus_dateline) */
    $handler->display->display_options['sorts']['field_focus_dateline_value']['id'] = 'field_focus_dateline_value';
    $handler->display->display_options['sorts']['field_focus_dateline_value']['table'] = 'field_data_field_focus_dateline';
    $handler->display->display_options['sorts']['field_focus_dateline_value']['field'] = 'field_focus_dateline_value';
    /* Contextual filter: Date: Date (node) */
    $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
    $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
    $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
    $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
    $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'focus_views_date_plugin';
    $handler->display->display_options['arguments']['date_argument']['granularity'] = 'second';
    $handler->display->display_options['arguments']['date_argument']['use_fromto'] = 'no';
    $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
      'field_data_field_focus_dateline.field_focus_dateline_value' => 'field_data_field_focus_dateline.field_focus_dateline_value',
    );
    $handler->display->display_options['arguments']['date_argument']['compare'] = '>';
    /* Filter criterion: Content: Published */
    $handler->display->display_options['filters']['status']['id'] = 'status';
    $handler->display->display_options['filters']['status']['table'] = 'node';
    $handler->display->display_options['filters']['status']['field'] = 'status';
    $handler->display->display_options['filters']['status']['value'] = 1;
    $handler->display->display_options['filters']['status']['group'] = 1;
    $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
    /* Filter criterion: Content: Type */
    $handler->display->display_options['filters']['type']['id'] = 'type';
    $handler->display->display_options['filters']['type']['table'] = 'node';
    $handler->display->display_options['filters']['type']['field'] = 'type';
    $handler->display->display_options['filters']['type']['value'] = array(
      'focus_article' => 'focus_article',
    );
    
    /* Display: Next Article */
    $handler = $view->new_display('block', 'Next Article', 'articlenext');
    $handler->display->display_options['block_description'] = 'Next Article';
    
    /* Display: Previous Article */
    $handler = $view->new_display('block', 'Previous Article', 'articleprev');
    $handler->display->display_options['defaults']['title'] = FALSE;
    $handler->display->display_options['title'] = 'Previous Article';
    $handler->display->display_options['defaults']['sorts'] = FALSE;
    /* Sort criterion: Content: Date (field_focus_dateline) */
    $handler->display->display_options['sorts']['field_focus_dateline_value']['id'] = 'field_focus_dateline_value';
    $handler->display->display_options['sorts']['field_focus_dateline_value']['table'] = 'field_data_field_focus_dateline';
    $handler->display->display_options['sorts']['field_focus_dateline_value']['field'] = 'field_focus_dateline_value';
    $handler->display->display_options['sorts']['field_focus_dateline_value']['order'] = 'DESC';
    $handler->display->display_options['defaults']['arguments'] = FALSE;
    /* Contextual filter: Date: Date (node) */
    $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
    $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
    $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
    $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
    $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'focus_views_date_plugin';
    $handler->display->display_options['arguments']['date_argument']['granularity'] = 'second';
    $handler->display->display_options['arguments']['date_argument']['use_fromto'] = 'no';
    $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
      'field_data_field_focus_dateline.field_focus_dateline_value' => 'field_data_field_focus_dateline.field_focus_dateline_value',
    );
    $handler->display->display_options['arguments']['date_argument']['compare'] = '<';
    $handler->display->display_options['block_description'] = 'Previous Article';

    // Add Sequential Articles View.
    $views[$view->name] = $view;
    
    return $views;
}
