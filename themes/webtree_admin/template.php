<?php
webtree_vanilla_includes(__FILE__);

/**
 * Implements hook_preprocess_template()
 * 
 * Controls output of maintenance theme
 */
function webtree_admin_preprocess_maintenance_page(&$vars) {
    drupal_add_css(WEBTREE_ADMIN_PATH.'/css/global.css', array('weight' => 10));
    drupal_add_css(WEBTREE_ADMIN_PATH.'/css/maintenance.css', array('weight' => 50));
    
    $vars['site_name'] = (function_exists('st')) ? st('WebTree') : t('WebTree');
    $vars['site_logo'] = theme('image', array('path' => WEBTREE_ADMIN_PATH.'/img/webtree.png'));
    $vars['footer'] = 'Footer goes here';
}