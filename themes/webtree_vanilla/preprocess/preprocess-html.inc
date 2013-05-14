<?php
/**
 * @file
 * Implements hook_preprocess_html()
 * 
 * @param {Array} $vars
 */

// add webtree base js file(s)
webtree_vanilla_load_js();

// add webtree base css file(s)
webtree_vanilla_load_css();

// add libraries
if (function_exists('libraries_detect')) {
    // add IE7.js if browser appropriate
    if (isset($_SERVER['HTTP_USER_AGENT'])) {
        
        // LTE IE 7
        if (preg_match('#msie [1-7]#i', $_SERVER['HTTP_USER_AGENT'])) {
            $library = libraries_detect('ie7-js');
            if ($library['installed']) {
                libraries_load('ie7-js');
            }
        }
        
        // LTE IE 8
        if (preg_match('#msie [1-8]#i', $_SERVER['HTTP_USER_AGENT'])) {
            $library = libraries_detect('html5shiv');
            if ($library['installed']) {
                libraries_load('html5shiv');
            }
        }
        
    }

    // add mobile detect library
    $library = libraries_detect('mobile-detect');
    if ($library['installed']) {
        libraries_load('mobile-detect');
        $detect = new Mobile_Detect();
        $vars['mobile'] = $detect->isMobile();
        $vars['attributes_array']['class'][] = ($detect->isMobile()) ? 'mobile-layout' : 'desktop-layout';
        drupal_add_js(array('webtreeMobile' => $detect->isMobile()), 'setting');
    }
    
    // add console.log-wrapper library
    $library = libraries_detect('console.log');
    if ($library['installed']) {
        libraries_load('console.log');
    }
}