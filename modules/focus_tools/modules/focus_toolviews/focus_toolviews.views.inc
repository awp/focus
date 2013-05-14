<?php
/**
 * @file
 * @todo
 */

/**
 * Implements hook_views_default_views()
 */
function focus_toolviews_views_default_views() {
    // Start downloads view
    $view = new View;
    $view->name = 'downloads';
    $view->description = '';
    $view->tag = 'default';
    $view->base_table = 'node';
    $view->human_name = 'Downloads';
    $view->core = 7;
    $view->api_version = '3.0';
    $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
    
    /* Display: Master */
    $handler = $view->new_display('default', 'Master', 'default');
    $handler->display->display_options['title'] = 'Downloads';
    $handler->display->display_options['use_more_always'] = FALSE;
    $handler->display->display_options['access']['type'] = 'perm';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'none';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['style_plugin'] = 'list';
    $handler->display->display_options['style_options']['grouping'] = array(
      0 => array(
        'field' => '',
        'rendered' => 1,
        'rendered_strip' => 0,
      ),
    );
    $handler->display->display_options['row_plugin'] = 'fields';
    /* Relationship: Content: Downloads (field_focus_download:fid) */
    $handler->display->display_options['relationships']['field_focus_download_fid']['id'] = 'field_focus_download_fid';
    $handler->display->display_options['relationships']['field_focus_download_fid']['table'] = 'field_data_field_focus_download';
    $handler->display->display_options['relationships']['field_focus_download_fid']['field'] = 'field_focus_download_fid';
    $handler->display->display_options['relationships']['field_focus_download_fid']['label'] = 'Downloads';
    $handler->display->display_options['relationships']['field_focus_download_fid']['required'] = TRUE;
    /* Field: File: Name */
    $handler->display->display_options['fields']['filename']['id'] = 'filename';
    $handler->display->display_options['fields']['filename']['table'] = 'file_managed';
    $handler->display->display_options['fields']['filename']['field'] = 'filename';
    $handler->display->display_options['fields']['filename']['relationship'] = 'field_focus_download_fid';
    $handler->display->display_options['fields']['filename']['label'] = '';
    $handler->display->display_options['fields']['filename']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['filename']['link_to_file'] = TRUE;
    /* Field: File: Size */
    $handler->display->display_options['fields']['filesize']['id'] = 'filesize';
    $handler->display->display_options['fields']['filesize']['table'] = 'file_managed';
    $handler->display->display_options['fields']['filesize']['field'] = 'filesize';
    $handler->display->display_options['fields']['filesize']['relationship'] = 'field_focus_download_fid';
    $handler->display->display_options['fields']['filesize']['label'] = '';
    $handler->display->display_options['fields']['filesize']['exclude'] = TRUE;
    $handler->display->display_options['fields']['filesize']['element_label_colon'] = FALSE;
    /* Field: File: Extension */
    $handler->display->display_options['fields']['extension']['id'] = 'extension';
    $handler->display->display_options['fields']['extension']['table'] = 'file_managed';
    $handler->display->display_options['fields']['extension']['field'] = 'extension';
    $handler->display->display_options['fields']['extension']['relationship'] = 'field_focus_download_fid';
    $handler->display->display_options['fields']['extension']['label'] = '';
    $handler->display->display_options['fields']['extension']['exclude'] = TRUE;
    $handler->display->display_options['fields']['extension']['element_label_colon'] = FALSE;
    /* Field: Global: Custom text */
    $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
    $handler->display->display_options['fields']['nothing']['table'] = 'views';
    $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
    $handler->display->display_options['fields']['nothing']['label'] = '';
    $handler->display->display_options['fields']['nothing']['alter']['text'] = '([filesize] [extension])';
    $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
    /* Sort criterion: Content: Post date */
    $handler->display->display_options['sorts']['created']['id'] = 'created';
    $handler->display->display_options['sorts']['created']['table'] = 'node';
    $handler->display->display_options['sorts']['created']['field'] = 'created';
    $handler->display->display_options['sorts']['created']['order'] = 'DESC';
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
    
    /* Display: Block */
    $handler = $view->new_display('block', 'Block', 'downloads');
    $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
    $handler->display->display_options['block_description'] = 'Downloads';
    
    // Add downloads view
    $views[$view->name] = $view;
    
    // Start gallery view
    $view = new View;
    $view->name = 'gallery';
    $view->description = '';
    $view->tag = 'default';
    $view->base_table = 'node';
    $view->human_name = 'Gallery';
    $view->core = 7;
    $view->api_version = '3.0';
    $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
    
    /* Display: Master */
    $handler = $view->new_display('default', 'Master', 'default');
    $handler->display->display_options['title'] = 'Related Photos:';
    $handler->display->display_options['use_more_always'] = FALSE;
    $handler->display->display_options['access']['type'] = 'perm';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'none';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['style_plugin'] = 'default';
    $handler->display->display_options['style_options']['grouping'] = array(
      0 => array(
        'field' => '',
        'rendered' => 1,
        'rendered_strip' => 0,
      ),
    );
    $handler->display->display_options['style_options']['row_class'] = 'grid-2';
    $handler->display->display_options['row_plugin'] = 'fields';
    /* Relationship: Content: Gallery Images (field_focus_gallery_image:fid) */
    $handler->display->display_options['relationships']['field_focus_gallery_image_fid']['id'] = 'field_focus_gallery_image_fid';
    $handler->display->display_options['relationships']['field_focus_gallery_image_fid']['table'] = 'field_data_field_focus_gallery_image';
    $handler->display->display_options['relationships']['field_focus_gallery_image_fid']['field'] = 'field_focus_gallery_image_fid';
    $handler->display->display_options['relationships']['field_focus_gallery_image_fid']['label'] = 'Gallery Images';
    $handler->display->display_options['relationships']['field_focus_gallery_image_fid']['required'] = TRUE;
    /* Field: Content: Gallery Images */
    $handler->display->display_options['fields']['field_focus_gallery_image']['id'] = 'field_focus_gallery_image';
    $handler->display->display_options['fields']['field_focus_gallery_image']['table'] = 'field_data_field_focus_gallery_image';
    $handler->display->display_options['fields']['field_focus_gallery_image']['field'] = 'field_focus_gallery_image';
    $handler->display->display_options['fields']['field_focus_gallery_image']['label'] = '';
    $handler->display->display_options['fields']['field_focus_gallery_image']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['field_focus_gallery_image']['click_sort_column'] = 'fid';
    $handler->display->display_options['fields']['field_focus_gallery_image']['type'] = 'colorbox';
    $handler->display->display_options['fields']['field_focus_gallery_image']['settings'] = array(
      'colorbox_node_style' => 'square_thumbnail',
      'colorbox_image_style' => 'large',
      'colorbox_gallery' => 'post',
      'colorbox_gallery_custom' => '',
      'colorbox_caption' => 'title',
      'colorbox_caption_custom' => '',
    );
    $handler->display->display_options['fields']['field_focus_gallery_image']['group_rows'] = FALSE;
    $handler->display->display_options['fields']['field_focus_gallery_image']['delta_offset'] = '0';
    /* Sort criterion: Content: Post date */
    $handler->display->display_options['sorts']['created']['id'] = 'created';
    $handler->display->display_options['sorts']['created']['table'] = 'node';
    $handler->display->display_options['sorts']['created']['field'] = 'created';
    $handler->display->display_options['sorts']['created']['order'] = 'DESC';
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
    
    /* Display: Block */
    $handler = $view->new_display('block', 'Block', 'gallery');
    $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
    $handler->display->display_options['block_description'] = 'Related Photos';
        
    // Add gallery view
    $views[$view->name] = $view;
    
    return $views;
}
