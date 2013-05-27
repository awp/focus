<?php
/**
 * @file
 * Contains functions that preprocess theme output.
 */


/**
 * Implements hook_preprocess_block()
 */
function focus_preprocess_block(&$vars) {
    switch ($vars['block']->module) {
        case 'views':
            // Add custom classes to view blocks based on view settings.
            if (strlen($vars['block']->delta) == 32) {
                // Retrive block delta from stored hashes.
                $hashes = variable_get('views_block_hashes', array());
                $delta  = $hashes[$vars['block']->delta];
            }
            else {
                $delta = $vars['block']->delta;
            }
            
            list($name, $display_id) = explode('-', $delta);
            
            if ($view = views_get_view($name)) {
                if ($view->access($display_id)) {
                    $view->set_display($display_id);
                    if (isset($view->display_handler)) {
                        // add block_css_class
                        if ($block_class = $view->display_handler->get_option('block_css_class')) {
                            $vars['classes_array'][] = $block_class;
                        }
                        
                        // add featured class
                        if ($block_featured = $view->display_handler->get_option('block_featured')) {
                            $vars['classes_array'][] = 'block-views-featured';
                        }
                    }
                }
                $view->destroy();
            }
        break;
    }
}
