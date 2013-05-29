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
    // Add contextual layout(s).
    if ($contexts = context_active_contexts()) {
        foreach ($contexts as $context_name => $context_info) {
            if (_vanilla_add_css($context_name)) {
                $added = TRUE;
            }
        }
    }
    
    if (empty($added)) {
        _vanilla_add_css('default');
    }
}