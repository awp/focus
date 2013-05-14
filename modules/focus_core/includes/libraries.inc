<?php
/**
 * @file
 * @todo
 */

/**
 * Implements hook_libraries_info()
 */
function focus_core_libraries_info() {
    
    $libraries['jquery.ui'] = array(
        'name' => 'jQuery UI',
        'vendor url' => 'https://github.com/jquery/jquery-ui',
        'download url' => 'https://github.com/jquery/jquery-ui.git',
        'version' => '1.8.24',
        'callbacks' => array(
            'pre-load' => array('_focus_core_preload_jquery_ui'),
        ),
        'files' => array(
            'js' => array(
                'ui/jquery.ui.core.js',
            ),
        ),
    );
    
    return $libraries;
    
}

/**
 * Libraries pre-load callback
 */
function _focus_core_preload_jquery_ui(&$library, $version, $variant) {
    $js_overrides = variable_get('focus_js_overrides', array());
    $css_overrides = variable_get('focus_css_overrides', array());
    
    $path = drupal_get_path('module', 'jquery_update');
    $files = scandir($library['library path'] . '/ui');
    
    foreach ($files as $file) {
        if (is_dir($file)) continue;
        if (FALSE === strpos($file, '.js')) continue;
        
        $minfile = str_replace('.js', '.min.js', $file);
        
        $js_overrides["misc/ui/$file"] = $library['library path'] . "/ui/$file";
        $js_overrides["$path/replace/ui/ui/minified/$file"] = $library['library path'] . "/ui/$file";
        $js_overrides["$path/replace/ui/ui/minified/$minfile"] = $library['library path'] . "/ui/$file";
    }
    
    $files = scandir($library['library path'] . '/themes/base');
    
    foreach ($files as $file) {
        if (is_dir($file)) continue;
        if (FALSE === strpos($file, '.css')) continue;
        
        $minfile = str_replace('.css', '.min.css', $file);
        
        $css_overrides["misc/ui/$file"] = $library['library path'] . "/themes/base/$file";
        $css_overrides["$path/replace/ui/themes/base/minified/$file"] = $library['library path'] . "/themes/base/$file";
        $css_overrides["$path/replace/ui/themes/base/minified/$minfile"] = $library['library path'] . "/themes/base/$file";
    }
    
    variable_set('focus_js_overrides', $js_overrides);
    variable_set('focus_css_overrides', $css_overrides);
}
