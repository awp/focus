<?php
/**
 * @file
 * Contains the theme's functions to manipulate Drupal's default markup.
 *
 * Complete documentation for this file is available online.
 * @see http://drupal.org/node/1728096
 */

define('VANILLA_PATH', drupal_get_path('theme', 'vanilla'));
require_once(dirname(__FILE__) . '/includes/helpers.inc');
require_once(dirname(__FILE__) . '/includes/libraries.inc');

/**
 * Implements hook_preprocess_html().
 */
function vanilla_preprocess_html(&$vars) {
    drupal_add_js(VANILLA_PATH . '/js/vanilla.js');

    // The following scripts are mostly IE dependent.
    // @see http://stackoverflow.com/questions/3855294/html5shiv-vs-dean-edwards-ie7-js-vs-modernizr-which-to-choose

    if (module_exists('libraries')) {
        // For some reason, libraries_detect needs to be run first to get the
        // load to work persistently.
        $library = libraries_detect('console.log');
        if (!empty($library['installed'])) {
            libraries_load('console.log');
        }

        $library = libraries_detect('jquery.custom-file-input');
        if (!empty($library['installed'])) {
            libraries_load('jquery.custom-file-input');
        }

        $library = libraries_detect('jquery.chosen');
        if (!empty($library['installed'])) {
            libraries_load('jquery.chosen');
            drupal_add_js(VANILLA_PATH . '/js/forms.js');
        }

        $library = libraries_detect('jquery.placeholder');
        if (!empty($library['installed'])) {
            libraries_load('jquery.placeholder');
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
    }

    // Add colorbox modifications.
    if (module_exists('colorbox')) {
        drupal_add_js(VANILLA_PATH . '/js/colorbox.js', array(
            'scope' => 'footer',
            'weight' => 100,
        ));
    }

    if (module_exists('context')) {
        if ($contexts = context_active_contexts()) {
            foreach ($contexts as $context_name => $context_info) {
                // Add contextual class to body.
                $vars['classes_array'][] = 'context-' . drupal_html_class($context_name);

                // Add contextual layout css.
                if (_vanilla_add_css($context_name)) {
                    $added = TRUE;
                }
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

    if ($detect = _vanilla_mobile_detect()) {
        if ($detect->isMobile()) {
            $vars['classes_array'][] = 'is-mobile';
        }

        if ($detect->isTablet()) {
            $vars['classes_array'][] = 'is-tablet';
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
 * Implements hook_process_page().
 */
function vanilla_process_page(&$vars) {
    if ($separator = filter_xss_admin(theme_get_setting('zen_breadcrumb_separator'))) {
        $vars['breadcrumb'] = preg_replace("#({$separator})#", '<span class="separator">$1</span>', $vars['breadcrumb']);
    }
}

/**
 * Implements hook_preprocess_block().
 */
function vanilla_preprocess_block(&$vars) {
    switch ($vars['block']->module) {
        case 'views':
            $hashes = variable_get('views_block_hashes', array());

            // Ensure all views blocks have a non-hashed id attribute.
            if (!empty($hashes[$vars['block']->delta])) {
                $delta = (strtr($hashes[$vars['block']->delta], '_', '-'));
                $vars['attributes_array']['id'] = 'block-views-' . $delta;
                $vars['block_html_id'] = 'block-views-' . $delta;
            }
            break;
    }
}

/**
 * Implements hook_preprocess_item_list().
 */
function vanilla_preprocess_item_list(&$vars) {
    if (empty($vars['attributes']['class']) || !is_array($vars['attributes']['class'])) {
        return;
    }

    if (in_array('pager', $vars['attributes']['class'])) {
        foreach ($vars['items'] as &$item) {
            if (!empty($item['class']) && in_array('pager-current', $item['class'])) {
                $item['data'] = '<span class="pager-current">' . $item['data'] . '</span>';
            }
        }
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
            'content'    => 'on',
        ),
    );

    // Get mobile metatag settings.
    $html5_respond_meta = array_filter((array) theme_get_setting('zen_html5_respond_meta'));
    if (in_array('meta', $html5_respond_meta)) {
        $elements['vanilla_mobile'] = array(
            '#type'   => 'html_tag',
            '#tag'    => 'meta',
            '#weight' => -5,
            '#attributes' => array(
                'name'    => 'MobileOptimized',
                'content' => 'width',
            ),
        );

        $elements['vanilla_handheld'] = array(
            '#type'   => 'html_tag',
            '#tag'    => 'meta',
            '#weight' => -5,
            '#attributes' => array(
                'name'    => 'HandheldFriendly',
                'content' => 'true',
            ),
        );

        $elements['vanilla_viewport'] = array(
            '#type'   => 'html_tag',
            '#tag'    => 'meta',
            '#weight' => -5,
            '#attributes' => array(
                'name'     => 'viewport',
                'content' => 'width=device-width',
            ),
        );
    }
}