<?php
/**
 * @file
 * Contains the theme's functions to manipulate Drupal's default markup.
 *
 * Complete documentation for this file is available online.
 * @see http://drupal.org/node/1728096
 */

/**
 * Implements hook_preprocess_html().
 */
function vanilla_preprocess_html(&$vars) {
    $path = drupal_get_path('theme', $GLOBALS['theme']);
    
    if (drupal_is_front_page()) {
        drupal_add_css("$path/css/home.css");
    }
    else {
        drupal_add_css("$path/css/inner.css");
    }
}

/**
 * Implements hook_css_alter().
 */
function vanilla_css_alter(&$css) {
    foreach ($css as $path => $info) {
        
    }
}
