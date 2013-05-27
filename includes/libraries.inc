<?php
/**
 * @file
 * Contains functions related to the Libraries API.
 */

/**
 * Implements hook_libraries_info().
 */
function focus_libraries_info() {
    $libraries['spyc'] = array(
        'name' => 'SPYC',
        'vendor url' => 'https://code.google.com/p/spyc/',
        'download url' => 'https://code.google.com/p/spyc/downloads/list',
        'version arguments' => array(
            'file' => 'spyc.php',
            'pattern' => '#version\s+([0-9a-zA-Z\.-]+)#i',
            'lines' => 4,
        ),
        'files' => array(
            'php' => array(
                'spyc.php',
            ),
        ),
    );
    
    return $libraries;
}
