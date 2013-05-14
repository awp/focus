<?php
/**
 * @file
 * Functions relevant to focus_tools configuration page(s).
 */

/**
 * drupal_get_form callback
 */
function focus_tools_fields_rebuild($form, &$form_state) {
    
    $types = node_type_get_types();
    $tools = module_implements('focus_content_type');
    
    $form['types'] = array(
        '#type' => 'fieldset',
        '#title' => t('Content Types'),
        '#description' => t('Rebuild fields for the following content types:'),
        '#tree' => TRUE,
    );
    
    foreach ($types as $type => $info) {
        if (!in_array($type, $tools)) continue;
        
        $form['types'][$type] = array(
            '#type' => 'checkbox',
            '#title' => $info->name,
        );
    }
    
    $vocabs = taxonomy_get_vocabularies();
    $tools  = module_implements('focus_taxonomy');
    
    $form['vocabs'] = array(
        '#type' => 'fieldset',
        '#title' => t('Taxonomies'),
        '#description' => t('Rebuild fields for the following taxonomies:'),
        '#tree' => TRUE,
    );

    foreach ($vocabs as $vocab) {
        if (!in_array($vocab->machine_name, $tools)) continue;
        
        $form['vocabs'][$vocab->machine_name] = array(
            '#type' => 'checkbox',
            '#title' => $vocab->name,
        );
    }
    
    $form['rebuild'] = array(
        '#type' => 'button',
        '#value' => t('Rebuild Fields'),
        '#executes_submit_callback' => TRUE,
        '#submit' => array('_focus_fields_rebuild'),
    );
    
    return $form;
}