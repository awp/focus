<?php
/**
 * @file
 * @todo
 */

/**
 * Implements hook_views_default_views()
 */
function focus_homepage_views_default_views() {
    $view = new view();
    $view->name = 'homepage_slideshow';
    $view->description = '';
    $view->tag = 'default';
    $view->base_table = 'node';
    $view->human_name = 'Homepage Slideshow';
    $view->core = 7;
    $view->api_version = '3.0';
    $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
    
    /* Display: Master */
    $handler = $view->new_display('default', 'Master', 'default');
    $handler->display->display_options['title'] = 'Homepage Slideshow';
    $handler->display->display_options['use_more_always'] = FALSE;
    $handler->display->display_options['access']['type'] = 'perm';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'none';
    $handler->display->display_options['style_plugin'] = 'slideshow';
    $handler->display->display_options['style_options']['slideshow_type'] = 'views_slideshow_cycle';
    $handler->display->display_options['style_options']['slideshow_skin'] = 'default';
    $handler->display->display_options['style_options']['skin_info'] = array(
      'class' => 'default',
      'name' => 'Default',
      'module' => 'views_slideshow',
      'path' => '',
      'stylesheets' => array(),
    );
    $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_pager']['weight'] = '1';
    $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_pager']['type'] = 'views_slideshow_pager_fields';
    $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_pager']['views_slideshow_pager_fields_fields'] = array(
      'field_focus_slide_title' => 0,
    );
    $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_controls']['weight'] = '1';
    $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_controls']['type'] = 'views_slideshow_controls_text';
    $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_slide_counter']['weight'] = '1';
    $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_pager']['enable'] = 1;
    $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_pager']['weight'] = '1';
    $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_pager']['type'] = 'views_slideshow_pager_fields';
    $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_pager']['views_slideshow_pager_fields_fields'] = array(
      'field_focus_slide_title' => 'field_focus_slide_title',
    );
    $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_controls']['weight'] = '1';
    $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_controls']['type'] = 'views_slideshow_controls_text';
    $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_slide_counter']['weight'] = '1';
    $handler->display->display_options['style_options']['views_slideshow_cycle']['transition_advanced'] = 1;
    $handler->display->display_options['style_options']['views_slideshow_cycle']['timeout'] = '5000';
    $handler->display->display_options['style_options']['views_slideshow_cycle']['speed'] = '700';
    $handler->display->display_options['style_options']['views_slideshow_cycle']['delay'] = '0';
    $handler->display->display_options['style_options']['views_slideshow_cycle']['action_advanced'] = 1;
    $handler->display->display_options['style_options']['views_slideshow_cycle']['start_paused'] = 0;
    $handler->display->display_options['style_options']['views_slideshow_cycle']['remember_slide_days'] = '1';
    $handler->display->display_options['style_options']['views_slideshow_cycle']['items_per_slide'] = '1';
    $handler->display->display_options['style_options']['views_slideshow_cycle']['wait_for_image_load_timeout'] = '3000';
    $handler->display->display_options['style_options']['views_slideshow_cycle']['cleartype'] = 0;
    $handler->display->display_options['style_options']['views_slideshow_cycle']['cleartypenobg'] = 0;
    $handler->display->display_options['row_plugin'] = 'fields';
    /* Relationship: Entity Reference: Referenced Entity */
    $handler->display->display_options['relationships']['field_focus_embedded_slideshow_target_id']['id'] = 'field_focus_embedded_slideshow_target_id';
    $handler->display->display_options['relationships']['field_focus_embedded_slideshow_target_id']['table'] = 'field_data_field_focus_embedded_slideshow';
    $handler->display->display_options['relationships']['field_focus_embedded_slideshow_target_id']['field'] = 'field_focus_embedded_slideshow_target_id';
    $handler->display->display_options['relationships']['field_focus_embedded_slideshow_target_id']['label'] = 'Slideshow';
    $handler->display->display_options['relationships']['field_focus_embedded_slideshow_target_id']['required'] = TRUE;
    /* Relationship: Content: Slides (field_focus_slideshow) */
    $handler->display->display_options['relationships']['field_focus_slideshow_value']['id'] = 'field_focus_slideshow_value';
    $handler->display->display_options['relationships']['field_focus_slideshow_value']['table'] = 'field_data_field_focus_slideshow';
    $handler->display->display_options['relationships']['field_focus_slideshow_value']['field'] = 'field_focus_slideshow_value';
    $handler->display->display_options['relationships']['field_focus_slideshow_value']['relationship'] = 'field_focus_embedded_slideshow_target_id';
    $handler->display->display_options['relationships']['field_focus_slideshow_value']['label'] = 'Slides';
    $handler->display->display_options['relationships']['field_focus_slideshow_value']['required'] = TRUE;
    $handler->display->display_options['relationships']['field_focus_slideshow_value']['delta'] = '-1';
    /* Field: Field collection item: Slide Image */
    $handler->display->display_options['fields']['field_focus_slide_image']['id'] = 'field_focus_slide_image';
    $handler->display->display_options['fields']['field_focus_slide_image']['table'] = 'field_data_field_focus_slide_image';
    $handler->display->display_options['fields']['field_focus_slide_image']['field'] = 'field_focus_slide_image';
    $handler->display->display_options['fields']['field_focus_slide_image']['relationship'] = 'field_focus_slideshow_value';
    $handler->display->display_options['fields']['field_focus_slide_image']['label'] = '';
    $handler->display->display_options['fields']['field_focus_slide_image']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['field_focus_slide_image']['click_sort_column'] = 'fid';
    $handler->display->display_options['fields']['field_focus_slide_image']['settings'] = array(
      'image_style' => 'slideshow',
      'image_link' => '',
    );
    /* Field: Field collection item: Slide Title */
    $handler->display->display_options['fields']['field_focus_slide_title']['id'] = 'field_focus_slide_title';
    $handler->display->display_options['fields']['field_focus_slide_title']['table'] = 'field_data_field_focus_slide_title';
    $handler->display->display_options['fields']['field_focus_slide_title']['field'] = 'field_focus_slide_title';
    $handler->display->display_options['fields']['field_focus_slide_title']['relationship'] = 'field_focus_slideshow_value';
    $handler->display->display_options['fields']['field_focus_slide_title']['label'] = '';
    $handler->display->display_options['fields']['field_focus_slide_title']['element_label_colon'] = FALSE;
    /* Field: Field collection item: Slide Caption */
    $handler->display->display_options['fields']['field_focus_slide_caption']['id'] = 'field_focus_slide_caption';
    $handler->display->display_options['fields']['field_focus_slide_caption']['table'] = 'field_data_field_focus_slide_caption';
    $handler->display->display_options['fields']['field_focus_slide_caption']['field'] = 'field_focus_slide_caption';
    $handler->display->display_options['fields']['field_focus_slide_caption']['relationship'] = 'field_focus_slideshow_value';
    $handler->display->display_options['fields']['field_focus_slide_caption']['label'] = '';
    $handler->display->display_options['fields']['field_focus_slide_caption']['element_label_colon'] = FALSE;
    /* Field: Field collection item: Slide Link */
    $handler->display->display_options['fields']['field_focus_slide_links']['id'] = 'field_focus_slide_links';
    $handler->display->display_options['fields']['field_focus_slide_links']['table'] = 'field_data_field_focus_slide_links';
    $handler->display->display_options['fields']['field_focus_slide_links']['field'] = 'field_focus_slide_links';
    $handler->display->display_options['fields']['field_focus_slide_links']['relationship'] = 'field_focus_slideshow_value';
    $handler->display->display_options['fields']['field_focus_slide_links']['label'] = '';
    $handler->display->display_options['fields']['field_focus_slide_links']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['field_focus_slide_links']['click_sort_column'] = 'url';
    $handler->display->display_options['fields']['field_focus_slide_links']['delta_offset'] = '0';
    $handler->display->display_options['fields']['field_focus_slide_links']['multi_type'] = 'ul';
    $handler->display->display_options['fields']['field_focus_slide_links']['separator'] = '';
    /* Sort criterion: Content: Slides (field_focus_slideshow:delta) */
    $handler->display->display_options['sorts']['delta']['id'] = 'delta';
    $handler->display->display_options['sorts']['delta']['table'] = 'field_data_field_focus_slideshow';
    $handler->display->display_options['sorts']['delta']['field'] = 'delta';
    $handler->display->display_options['sorts']['delta']['relationship'] = 'field_focus_embedded_slideshow_target_id';
    /* Contextual filter: Content: Nid */
    $handler->display->display_options['arguments']['nid']['id'] = 'nid';
    $handler->display->display_options['arguments']['nid']['table'] = 'node';
    $handler->display->display_options['arguments']['nid']['field'] = 'nid';
    $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
    $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
    $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
    $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
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
      'focus_homepage' => 'focus_homepage',
    );
    
    /* Display: Slideshow */
    $handler = $view->new_display('block', 'Slideshow', 'block');
    $handler->display->display_options['block_description'] = 'Homepage Slideshow';

    // Add Homepage Slideshow View.
    $views[$view->name] = $view;
    
    return $views;
}
