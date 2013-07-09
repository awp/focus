<?php
/**
 * @file
 * Implements hook_preprocess_node().
 */

// Provide a class for nodes based on their view_mode.
if (!empty($vars['view_mode'])) {
    if (!in_array('node-' . $vars['view_mode'], $vars['attributes_array']['class'])) {
        $vars['attributes_array']['class'][] = 'node-' . $vars['view_mode'];
    }
}