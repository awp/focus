<?php
/**
 * @file
 * Contains the theme's functions to manipulate Drupal's default markup.
 *
 * Complete documentation for this file is available online.
 * @see http://drupal.org/node/1728096
 */

require_once(dirname(__FILE__) . '/includes/helpers.inc');

/**
 * Implements hook_preprocess_html().
 */
function vanilla_preprocess_html(&$vars) {
    if (drupal_is_front_page()) {
        _vanilla_add_css('home');
    }
    else {
        _vanilla_add_css('inner');
    }
    
    // Add contextual layout(s).
    if ($contexts = context_active_contexts()) {
        foreach ($contexts as $context_name => $context_info) {
            $added = _vanilla_add_css('contexts/' . $context_name);
        }
    }

    if (empty($added)) {
        _vanilla_add_css('contexts/default');
    }
}