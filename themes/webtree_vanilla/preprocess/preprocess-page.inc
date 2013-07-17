<?php
/**
 * @file
 * Implements hook_preprocess_page()
 *
 * @param {Array} $vars
 */

if (drupal_is_front_page() && (variable_get('site_frontpage', '') == '' || variable_get('site_frontpage', '') == 'node')) {
    // remove 'no front page content has been created yet'
    $vars['page']['content']['content']['content']['system_main']['default_message'] =
    $vars['page']['content']['content']['content']['system_main']['content']['default_message'] = array();
    unset($vars['page']['content']['content']['content']['system_main']);
}