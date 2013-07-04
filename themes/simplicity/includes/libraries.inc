<?php
/**
 * @file
 * Contains all functions related to the libraries API.
 */

/**
 * Implements hook_libraries_info_alter().
 */
function simplicity_libraries_info() {
    $libraries['jquery.chosen'] = array(
        'name' => 'Chosen',
        'vendor url' => 'http://harvesthq.github.io/chosen/',
        'download url' => 'http://chosen.getharvest.com.s3.amazonaws.com/chosen_v0.11.1.zip',
        // Using the license year as this project is not versioned.
        'version arguments' => array(
            'file' => 'chosen.jquery.min.js',
            'pattern' => '/v([\d].[\d].[\d])/i',
            'lines' => 1,
        ),
        'callbacks' => array(),
        'files' => array(
            'js' => array(
                'chosen.jquery.min.js',
            ),
        ),
    );

    return $libraries;
}
