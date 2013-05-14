<?php
/**
 * @file
 * Implements hook_preprocess_block()
 * 
 * @param {Array} $vars
 */

switch ($vars['block']->module) {
    case 'views':
        $hashes = variable_get('views_block_hashes', array());
        
        // ensure all views blocks have a non-hashed id attribute
        if (!empty($hashes[$vars['block']->delta])) {
            $vars['attributes_array']['id'] = 'block-views-' . (strtr($hashes[$vars['block']->delta], '_', '-'));
        }
    break;
}
