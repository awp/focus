<?php
/**
 * @file
 * Contains all functions related to the libraries API.
 */

/**
 * Implements hook_libraries_info_alter().
 */
function vanilla_libraries_info() {
    $libraries['console.log'] = array(
        'name' => 'Console.log',
        'vendor url' => 'http://patik.com/blog/complete-cross-browser-console-log/',
        'download url' => 'https://github.com/cpatik/console.log-wrapper/zipball/master',
        // Using the license year as this project is not versioned.
        'version arguments' => array(
            'file' => 'LICENSE',
            'pattern' => '/\(c\)\s([\d]+)/i',
            'lines' => 6,
        ),
        'callbacks' => array(),
        'files' => array(
            'js' => array(
                'consolelog.min.js',
            ),
        ),
    );
    
    $libraries['ie7-js'] = array(
        'name' => 'IE9js',
        'vendor url' => 'https://code.google.com/p/ie7-js/',
        'download url' => 'https://code.google.com/p/ie7-js/',
        'version arguments' => array(
            'file' => 'IE9.js',
            'pattern' => '/version:"(.*?)"/i',
            'lines' => 6,
        ),
        'files' => array(
            'js' => array(
                'IE9.js' => array(
                    'browsers' => array(
                        'IE' => 'lt IE 9',
                        '!IE' => FALSE,
                    ),
                ),
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
                'dist/html5shiv.js' => array(
                    'browsers' => array(
                        'IE' => 'lt IE 9',
                        '!IE' => FALSE,
                    ),
                ),
            ),
        ),
    );
    
    $libraries['respondjs'] = array(
        'name' => 'HTML5 Shiv',
        'vendor url' => 'https://github.com/scottjehl/Respond',
        'download url' => 'https://github.com/scottjehl/Respond/archive/master.zip',
        // Using the git ref as this project is not versioned.
        'version' => '2c59aebba',
        'files' => array(
            'js' => array(
                'respond.min.js' => array(
                    'browsers' => array(
                        'IE' => 'lte IE 9',
                        '!IE' => FALSE,
                    ),
                ),
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
        'files' => array(
            'js' => array(
                'ui/jquery.ui.position.js',
                'ui/jquery.ui.selectmenu.js',
            ),
            'css' => array(
                'themes/base/jquery.ui.selectmenu.css',
            ),
        ),
        // 'dependencies' => array('jquery.ui'),
    );
    
    return $libraries;
}
