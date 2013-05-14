<?php
/**
 * @file
 * Implements hook_process_region().
 * 
 * @param array $vars by reference
 */
 
switch ($vars['region']) {
    case 'menu':
        // alter main menu output to display children as well
        $menu_tree_page_data = menu_tree_page_data(variable_get('menu_main_links_source', 'main-menu'));
        $vars['main_menu'] = menu_tree_output($menu_tree_page_data);
    break;
}
