<?php
/**
 * @file
 * Contains the theme's functions to manipulate Drupal's default markup.
 *
 * Complete documentation for this file is available online.
 * @see http://drupal.org/node/1728096
 */

require_once(dirname(__FILE__) . '/includes/helpers.inc');
require_once(dirname(__FILE__) . '/includes/libraries.inc');

/**
 * Implements hook_preprocess_html().
 */
function vanilla_preprocess_html(&$vars) {
    // The following scripts are mostly IE dependent.
    // @see http://stackoverflow.com/questions/3855294/html5shiv-vs-dean-edwards-ie7-js-vs-modernizr-which-to-choose
    
    // For some reason, libraries_detect needs to be run first to get the 
    // load to work persistently.
    $library = libraries_detect('console.log');
    if (!empty($library['installed'])) {
        libraries_load('console.log');
    }
    
    $library = libraries_detect('ie7-js');
    if (!empty($library['installed'])) {
        libraries_load('ie7-js');
    }
    
    $library = libraries_detect('respondjs');
    if (!empty($library['installed']) && $vars['add_respond_js']) {
        libraries_load('respondjs');
    }
    else {
        $library = libraries_detect('html5shiv');
        if (!empty($library['installed']) && $vars['add_html5_shim']) {
            libraries_load('html5shiv');
        }
    }
    
    // Add contextual layout css.
    if ($contexts = context_active_contexts()) {
        foreach ($contexts as $context_name => $context_info) {
            if (_vanilla_add_css($context_name)) {
                $added = TRUE;
            }
        }
    }
    
    // If no matches, try adding a generic layout based on contexts.
    if (empty($added)) {
        foreach ($contexts as $context_name => $context_info) {
            if (FALSE === strpos($context_name, '_')) continue;

            $parts = explode('_', $context_name);
            $part  = reset($parts);
            if (_vanilla_add_css($part)) {
                $added = TRUE;
                break;
            }
        }
        
        if (empty($added)) {
            _vanilla_add_css('default');
        }
    }
}

/**
 * Implements hook_preprocess_page().
 */
function vanilla_preprocess_page(&$vars) {
    if (!empty($vars['node']->type)) {
        $vars['theme_hook_suggestions'][] = 'page__' . $vars['node']->type;
    }
}

/**
 * Implements hook_page_alter().
 */
function vanilla_page_alter(&$page) {
    $skip_link_anchor = theme_get_setting('zen_skip_link_anchor');
    $skip_link_text   = theme_get_setting('zen_skip_link_text');
    
    if ($skip_link_text && $skip_link_anchor) {
        $page['page_top']['vanilla_skip_link'] = array(
            '#type' => 'container',
            '#attributes' => array('id' => 'skip-link'),
            '#weight' => -9999,
            '#children' => l($skip_link_text, '', array(
                'fragment' => $skip_link_anchor,
                'attributes' => array(
                    'class' => array(
                        'element-invisible',
                        'element-focusable',
                    ),
                ),
            )),
        );
    }
}

/**
 * Implements hook_html_head_alter().
 */
function vanilla_html_head_alter(&$elements) {
    // Add IE X-UA-Compatible tag, forcing latest version rendering.
    $elements['vanilla_xua'] = array(
        '#type' => 'html_tag',
        '#tag'  => 'meta',
        '#weight' => -10,
        '#attributes' => array(
            'http-equiv' => 'X-UA-Compatible',
            'content'    => 'IE=edge,chrome=1',
        ),
    );
    
    // Add cleartype.
    $elements['vanilla_cleartype'] = array(
        '#type'   => 'html_tag',
        '#tag'    => 'meta',
        '#weight' => -9,
        '#attributes' => array(
            'http-equiv' => 'cleartype',
            'contents'   => 'on',
        ),
    );
    
    // Get mobile metatag settings.
    $html5_respond_meta = array_filter((array) theme_get_setting('zen_html5_respond_meta'));
    if (in_array('meta', $html5_respond_meta)) {
        // Add cleartype.
        $elements['vanilla_mobile'] = array(
            '#type'   => 'html_tag',
            '#tag'    => 'meta',
            '#weight' => -5,
            '#attributes' => array(
                'name'     => 'MobileOptimized',
                'contents' => 'width',
            ),
        );
        // Add cleartype.
        $elements['vanilla_handheld'] = array(
            '#type'   => 'html_tag',
            '#tag'    => 'meta',
            '#weight' => -5,
            '#attributes' => array(
                'name'     => 'HandheldFriendly',
                'contents' => 'true',
            ),
        );
        // Add cleartype.
        $elements['vanilla_viewport'] = array(
            '#type'   => 'html_tag',
            '#tag'    => 'meta',
            '#weight' => -5,
            '#attributes' => array(
                'name'     => 'viewport',
                'viewport' => 'width=device-width',
            ),
        );
    }

}
