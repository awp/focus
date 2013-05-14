<?php
/**
 * Implements hook_preprocess_region()
 * 
 * @param array $vars
 */
 
switch ($vars['region']) {
    case 'menu':
        // Build variables for Primary and Secondary local tasks
        $vars['primary_local_tasks'] = menu_primary_local_tasks();
        $vars['secondary_local_tasks'] = menu_secondary_local_tasks();
    break;
}
