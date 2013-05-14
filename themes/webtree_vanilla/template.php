<?php
/**
 * @file
 * Theme: webtree_vanilla
 */

webtree_vanilla_includes(__FILE__);

/**
 * Provides auto-disocvery of any include files for a given theme
 */
function webtree_vanilla_includes($file) {
    $path = dirname($file);
    $includes = glob("$path/includes/*.inc");
    foreach ($includes as $include) {
        require_once($include);
    }
}

/**
 * Implements hook_form_system_theme_settings_alter()
 * Adds 'full' width options to zone and region grid settings
 * Allows certain sections to pop out of the grid and expand to full-screen width
 */
function webtree_vanilla_form_system_theme_settings_alter(&$form, &$form_state) {
    
    if (empty($form_state['build_info']['args'])) return;
    if ($GLOBALS['theme_key'] != $form_state['build_info']['args'][0]) return;

    $theme = alpha_get_theme();
    $containers = isset($theme->grids[$theme->settings['grid']]) ? webtree_vanilla_container_options($theme->grids[$theme->settings['grid']]) : array();
    $columns = $spacing = !empty($containers) ? webtree_vanilla_column_options(max(array_keys($containers))) : array();
    
    // Create a container width selection menu for EACH zone
    foreach ($theme->zones as $zone => $item) {
        $section = $item['enabled'] ? $item['section'] : '__unassigned__';
        
        $form['alpha_settings']['structure'][$section][$zone]['zone']['alpha_zone_' . $zone . '_columns'] = array(
            '#type' => 'select',
            '#title' => t('Column count'),
            '#default_value' => $item['columns'],
            '#options' => $containers,
        );
    }
    
    // Create a container width selection menu for EACH region
    foreach ($theme->regions as $region => $item) {
        $zone = $item['enabled'] ? $item['zone'] : '__unassigned__';
        $section = $item['enabled'] && $theme->zones[$item['zone']]['enabled'] ? $item['section'] : '__unassigned__';
        
        $form['alpha_settings']['structure'][$section][$zone]['regions'][$region]['alpha_region_' . $region . '_columns'] = array(
            '#type' => 'select',
            '#title' => t('Width'),
            '#default_value' => $item['columns'],
            '#options' => $columns,
        );
    }
    
}

/**
 * Implements hook_form_alter
 * Attaches custom webtree forms script to all forms
 */
function webtree_vanilla_form_alter(&$form, &$form_state, $form_id) {
    // if (drupal_get_bootstrap_phase() == DRUPAL_BOOTSTRAP_FULL)
    $form['#attached']['js'][] = WEBTREE_VANILLA_PATH . '/js/webtree_forms.js';
}

/**
 * Implements hook_preprocess_webform_form().
 */
// function webtree_vanilla_preprocess_webform_form(&$vars) {
    // $components = &$vars['form']['submitted'];
    // foreach (element_children($components) as $key) {
        // if (!empty($components[$key]['#default_value'])) {
            // $components[$key]['#attributes']['data-title'] = $components[$key]['#default_value'];
        // }
    // }
// }

/**
 * Implements hook_css_alter()
 */
function webtree_vanilla_css_alter(&$css) {
    $css_overrides = variable_get('webtree_css_overrides', array());

    foreach ($css_overrides as $old => $new) {
        if (empty($css[$old])) continue;
        $css[$new] = $css[$old];
        $css[$new]['data'] = $new;
        
        unset($css[$old]);
    }
}

/**
 * Implements hook_js_alter()
 */
function webtree_vanilla_js_alter(&$javascript) {
    
    // remove overridden javascripts
    $js_overrides = variable_get('webtree_js_overrides', array());
    
    // foreach ($js_overrides as $old => $new) {
        // if (empty($javascript[$old])) continue;
        // $javascript[$new] = $javascript[$old];
        // $javascript[$new]['data'] = $new;
        // $javascript[$new]['version'] = '1.8.24';
//         
        // unset($javascript[$old]);
    // }

}

/**
 * Implements theme_breadcrumb()
 * Builds better markup for breadcrumb styling
 */
function webtree_vanilla_breadcrumb($variables) {
    
    $breadcrumb = $variables['breadcrumb'];
    $separator  = (empty($variables['separator'])) ? '&rsaquo;' : $variables['separator'];
    
    if ($node = node_load(arg(1))) {
        switch (arg(2)) {
            case 'children': $breadcrumb[] = 'Children'; break;
            case 'edit': $breadcrumb[] = 'Edit'; break;
            default: $breadcrumb[] = (empty($node->nodehierarchy_menu_links[0]['link_title']))
                ? $node->title
                : $node->nodehierarchy_menu_links[0]['link_title'];
        }
    }

    if (!empty($breadcrumb)) {
        return '<div class="breadcrumbs">' . implode("<span class='breadcrumb-separator'>$separator</span>", $breadcrumb) . '</div>';
    }
    
}

/**
 * Implements hook_preprocess_template()
 */
function webtree_vanilla_preprocess_maintenance_page(&$vars) {
    webtree_vanilla_load_css();
    webtree_vanilla_load_js();
}

/**
 * Implements hook_process_region().
 */
function webtree_vanilla_process_region(&$vars) {
    if (in_array($vars['elements']['#region'], array('content', 'branding'))) {
        $theme = alpha_get_theme();

        switch ($vars['elements']['#region']) {
            case 'content':
                $vars['title'] = (empty($GLOBALS['title_replaced'])) ? $theme->page['title'] : FALSE;
                break;
    
            case 'branding':
                $vars['linked_logo_img'] = _webtree_vanilla_linked_logo_make($theme->page['logo'], $vars['site_name']);
                break;
        }
    }
}