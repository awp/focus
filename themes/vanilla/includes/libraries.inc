<?php
/**
 * @file
 * Contains all functions related to the libraries API.
 */

/**
 * Implements hook_libraries_info_alter().
 */
function vanilla_libraries_info() {
    $libraries['json2'] = array(
        'name' => 'JSON2',
        'vendor url' => 'https://github.com/douglascrockford/JSON-js',
        'download url' => 'git://github.com/douglascrockford/JSON-js.git',
        'version' => '43d7836', // using the git ref as this project is not versioned
        'files' => array(
            'js' => array(
                'json2.js',
            ),
        ),
    );

    $libraries['jquery.custom-file-input'] = array(
        'name' => 'jQuery Custom File Input',
        'vendor url' => 'https://github.com/filamentgroup/jQuery-Custom-File-Input',
        'download url' => 'https://github.com/filamentgroup/jQuery-Custom-File-Input/archive/master.zip',
        'version' => '27dfbe7c79', // using the git ref as this project is not versioned
        'files' => array(
            'js' => array(
                'js/jQuery.fileinput.js',
            ),
        ),
    );

    $libraries['jquery.placeholder'] = array(
        'name' => 'jQuery Placeholder',
        'vendor url' => 'https://github.com/mathiasbynens/jquery-placeholder',
        'download url' => 'https://github.com/mathiasbynens/jquery-placeholder/archive/master.zip',
        'version arguments' => array(
            'file' => 'jquery.placeholder.js',
            'pattern' => '/v([\d]\.[\d]\.[\d])/i',
            'lines' => 1,
        ),
        'files' => array(
            'js' => array(
                'jquery.placeholder.js',
            ),
        ),
    );

    $libraries['jquery.chosen'] = array(
        'name' => 'Chosen',
        'vendor url' => 'http://harvesthq.github.io/chosen/',
        'download url' => 'http://chosen.getharvest.com.s3.amazonaws.com/chosen_v0.11.1.zip',
        'version arguments' => array(
            'file' => 'chosen.jquery.min.js',
            'pattern' => '/v([\d].[\d]{1,2}.[\d]{1,2})/i',
            'lines' => 1,
        ),
        'files' => array(
            'css' => array(
                'chosen.min.css',
            ),
            'js' => array(
                'chosen.jquery.min.js',
            ),
        ),
    );

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
        'files' => array(
            'js' => array(
                'consolelog.min.js',
            ),
        ),
    );

    $libraries['spin-js'] = array(
        'name' => 'Spin.js',
        'vendor url' => 'https://github.com/fgnass/spin.js/',
        'download url' => 'https://github.com/fgnass/spin.js/',
        'version arguments' => array(
            'file' => 'package.json',
            'pattern' => '@([\d]\.[\d]\.[\d])@i',
            'lines' => 3,
        ),
        'files' => array(
            'js' => array(
                'spin.min.js',
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
            'pattern' => '/\@version.*?([\d]+\.[\d]+\.[\d]+)/i',
            'lines' => 32,
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
    );

    $libraries['jquery.cycle'] = array(
        'name' => 'jQuery Cycle',
        'vendor url' => 'http://malsup.com/jquery/cycle/',
        'download url' => 'http://malsup.com/jquery/cycle/download.html',
        'version arguments' => array(
            'file' => 'jquery.cycle.all.js',
            'pattern' => '/([\d]\.[\d]\.[\d])/i',
            'lines' => 5,
        ),
        'files' => array(
            'js' => array(
                'jquery.cycle.all.js',
            ),
        ),
    );

    return $libraries;
}
