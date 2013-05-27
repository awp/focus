<?php
/**
 * @file
 * Contains functions providing default date configurations.
 */

/**
 * Implements hook_date_format_types()
 */
function focus_date_format_types() {
    return array(
        'longdate' => t('Long Date'),
        'mediumdate' => t('Medium Date'),
        'shortdate' => t('Short Date'),
        'tiny' => t('Tiny'),
        'year' => t('Year'),
        'time' => t('Time'),
    );
}

/**
 * Implements hook_date_formats()
 */
function focus_date_formats() {
    return array(
        array(
            'type' => 'longdate',
            'format' => 'l, F j, Y',
            'locales' => array('en', 'en-us'),
        ),
        array(
            'type' => 'mediumdate',
            'format' => 'F j, Y',
            'locales' => array('en', 'en-us'),
        ),
        array(
            'type' => 'shortdate',
            'format' => 'M j Y',
            'locales' => array('en', 'en-us'),
        ),
        array(
            'type' => 'tiny',
            'format' => 'n/j/y',
            'locales' => array('en', 'en-us'),
        ),
        array(
            'type' => 'tiny',
            'format' => 'j/n/y',
            'locales' => array(),
        ),
        array(
            'type' => 'tiny',
            'format' => 'y/j/n',
            'locales' => array(),
        ),
        array(
            'type' => 'year',
            'format' => 'Y',
            'locales' => array(),
        ),
        array(
            'type' => 'time',
            'format' => 'g:ia',
            'locales' => array(),
        ),
        array(
            'type' => 'time',
            'format' => 'h:ia',
            'locales' => array(),
        ),
        array(
            'type' => 'time',
            'format' => 'G:i',
            'locales' => array(),
        ),
        array(
            'type' => 'time',
            'format' => 'H:i',
            'locales' => array(),
        ),
    );  
}
