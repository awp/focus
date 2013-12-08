<?php
/**
 * @file
 * Contains functions related to the Libraries API.
 */

/**
 * Implements hook_libraries_info().
 */
function webtree_vanilla_libraries_info() {
    $libraries['jquery.placeholder'] = array(
        'name' => 'jQuery Placeholder',
        'vendor url' => 'https://github.com/mathiasbynens/jquery-placeholder',
        'download url' => 'https://github.com/mathiasbynens/jquery-placeholder/archive/master.zip',
        'version arguments' => array(
            'file' => 'jquery.placeholder.js',
            'pattern' => '/v(.*?)[\s]/i',
            'lines' => 1,
        ),
        'files' => array(
            'js' => array(
                'jquery.placeholder.js',
            ),
        ),
    );

    $libraries['console.log'] = array(
        'name' => 'Console.log',
        'vendor url' => 'http://patik.com/blog/complete-cross-browser-console-log/',
        'download url' => 'https://github.com/cpatik/console.log-wrapper/zipball/master',
        'version' => '4648a1ec80', // using the git ref as this project is not versioned
        'files' => array(
            'js' => array(
                'consolelog.min.js',
            ),
        ),
    );

    $libraries['html5shiv'] = array(
        'name' => 'HTML5 Shiv',
        'vendor url' => 'https://code.google.com/p/html5shiv/',
        'download url' => 'https://github.com/aFarkas/html5shiv/zipball/master',
        'version arguments' => array(
            'file' => 'dist/html5shiv.js',
            'pattern' => '/v([\d]\.[\d]\.[\d])/i',
            'lines' => 3
        ),
        'files' => array(
            'js' => array(
                'dist/html5shiv.js',
            ),
        ),
    );

    $libraries['mobile-detect'] = array(
        'name' => 'Mobile Detect',
        'vendor url' => 'https://github.com/serbanghita/Mobile-Detect',
        'download url' => 'https://github.com/serbanghita/Mobile-Detect.git',
        'version arguments' => array(
            'file' => 'Mobile_Detect.php',
            'pattern' => '/\'([\d]\.[\d]\.[\d])\'/i',
            'lines' => 50,
        ),
        'files' => array(
            'php' => array(
                'Mobile_Detect.php',
            ),
        ),
    );

    $libraries['jquery.ui.selectmenu'] = array(
        'name' => 'jQuery UI - Selectmenu',
        'vendor url' => 'https://github.com/fnagel/jquery-ui',
        'download url' => 'https://github.com/fnagel/jquery-ui/zipball/selectmenu_v1.3.0',
        'version arguments' => array(
            'file' => 'ui/jquery.ui.selectmenu.js',
            'pattern' => '/([\d]\.[\d]\.[\d])/i',
            'lines' => 5,
        ),
        'callbacks' => array(
            'pre-load' => array('webtree_vanilla_ui_selectmenu_preload'),
        ),
        'files' => array(
            'js' => array(
                'ui/jquery.ui.position.js',
                'ui/jquery.ui.selectmenu.js',
            ),
            'css' => array(
                'themes/base/jquery.ui.selectmenu.css',
            ),
        ),
    );

    return $libraries;
}

function webtree_vanilla_ui_selectmenu_preload() {
    drupal_add_library('system', 'ui.widget');
    drupal_add_library('system', 'ui.position');
}
