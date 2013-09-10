<?php
/**
 * @file
 * Set of helper functions available to the WebTree Vanilla theme and subthemes
 */

/**
 * Load base webtree_vanilla css
 */
function webtree_vanilla_load_css() {
    drupal_add_css(WEBTREE_VANILLA_PATH . '/css/webtree.css', array('group' => CSS_SYSTEM - 1, 'weight' => -500));

    // add active theme font css file
    webtree_vanilla_add_css('fonts.css', array('group' => CSS_SYSTEM - 1, 'weight' => -999));

    // add active theme retina stylesheet
    $media = array(
        'only screen and (-webkit-min-device-pixel-ratio: 2)',
        'only screen and (min--moz-device-pixel-ratio: 2)',
        'only screen and (-o-device-pixel-ratio: 2)',
        'only screen and (min-device-pixel-ratio: 2)',
    );
    webtree_vanilla_add_css('retina.css', array('group' => 9999, 'weight' => 999, 'media' => implode(',', $media)));

    // add active theme colorbox styles
    webtree_vanilla_add_css('colorbox.css');

    // no additional customizations for maintenance mode
    // TODO: consider a separate webtree_mmaintenance theme for maintenance mode
    if (defined('MAINTENANCE_MODE')) return;

    // add active theme global css based on home/inner context
    if (drupal_is_front_page()) webtree_vanilla_add_css('global-home.css', array('group' => CSS_THEME, 'weight' => 10));
    else webtree_vanilla_add_css('global-inner.css', array('group' => CSS_THEME, 'weight' => 10));

    // if using context module, add optional context-specific css files and add classes to body
    if (function_exists('context_active_contexts')) {
        $contexts = context_active_contexts();

        foreach ($contexts as $context => $info) {
            $cleaned = str_replace('_', '-', $context);
            webtree_vanilla_add_css("context/$cleaned.css", array('group' => CSS_THEME, 'weight' => 11));

            $vars['attributes_array']['class'][] = "context-$cleaned";
        }
    }

    // if user is logged in, add extra styles for authenticated users
    if (user_is_logged_in()) {
        webtree_vanilla_add_css('global-admin.css', array('group' => CSS_THEME, 'weight' => 12));
    }

}

/**
 * Load base webtree_vanilla js
 */
function webtree_vanilla_load_js() {
    // TODO: manage these as optional add-ons in config
    drupal_add_library('system', 'ui.button');

    if (function_exists('libraries_load')) {
        // add selectmenu and appropriate theme styles
        $library = libraries_detect('jquery.ui.selectmenu');
        if (!empty($library['installed'])) {
            libraries_load('jquery.ui.selectmenu');
            drupal_add_js(drupal_get_path('theme', 'webtree_vanilla') . '/js/selectmenu.js');
        }

        drupal_add_css(WEBTREE_VANILLA_PATH . '/css/ui.css', array('group' => CSS_THEME, 'weight' => -10));
        webtree_vanilla_add_css('ui.selectmenu.css');

        // TODO: DEPRECATED
        // Expire Sept 30, 2013
        // Naming a css file in a custom theme jquery.ui.selectmenu.css prevents
        // the core selectmenu styles from being loaded.
        // webtree_vanilla_add_css('jquery.ui.selectmenu.css');
    }

    // no additional customizations for maintenance mode
    if (defined('MAINTENANCE_MODE')) return;

    drupal_add_js(WEBTREE_VANILLA_PATH . '/js/webtree.js', array('scope' => 'footer', 'weight' => 100));

    webtree_vanilla_add_theme_js();
}

/**
 * Extends alpha_container_options()
 */
function webtree_vanilla_container_options($grid) {
    $containers = alpha_container_options($grid);
    return $containers; //$containers + array('full-12' => 'Full 12 Column', 'full-16' => 'Full 16 Column', 'full-24', 'Full 24 Column');
}

/**
 * Extends alpha_column_options()
 */
function webtree_vanilla_column_options($containers) {
    $columns = alpha_column_options($containers);
    return $columns + array('full' => 'Full');
}

/**
 * Handle theme-specific css loading
 * Checks if file exists before attempting to add
 */
function webtree_vanilla_add_css($file, $options = array()) {
    $theme = alpha_get_theme();
    $path  = drupal_get_path('theme', $theme->theme);

    if (file_exists("$path/css/$file")) drupal_add_css("$path/css/$file", $options);
}

/**
 * Handle theme-specific js loading
 * Checks if file exists before attempting to add
 */
function webtree_vanilla_add_theme_js($group = JS_THEME, $weight = 0) {
    $theme = alpha_get_theme();
    $path  = drupal_get_path('theme', $theme->theme);

    if (file_exists("$path/js/{$theme->theme}.js")) drupal_add_js("$path/js/{$theme->theme}.js", array('group' => $group, 'weight' => $weight));
}

/**
 * @todo
 */
function _webtree_vanilla_linked_logo_make($logo, $name) {

    global $base_path;
    $theme = alpha_get_theme();

    $logo = preg_replace('#.*?(sites\/)#i', '$1', $logo);

    $dynamic = explode('/', $logo);
    $null = array_pop($dynamic);
    $dynamic = implode('/', $dynamic) . '/img/logo.png';

    $options = array(
        'html' => TRUE,
        'attributes' => array(
            'rel' => 'home',
            'title' => check_plain($name),
        ),
    );

    $img = ($theme->page['logo']) ? '<img src="' . $theme->page['logo'] . '" alt="' . check_plain($theme->page['site_name']) . '" id="logo" />' : '';

    if (file_exists(DRUPAL_ROOT . '/' . $dynamic)) {
        $options['attributes']['style'] = "background: url(" . $base_path . $dynamic . ") no-repeat";
        $img = check_plain($name);
    }

    return l($img, '<front>', $options);

}
