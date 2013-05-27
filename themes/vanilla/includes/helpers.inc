<?php
/**
 * @file
 * Provides helper functions for the vanilla base theme.
 */

/**
 * Gets the path to the current theme.
 */
function _vanilla_active_theme_path() {
    static $path;
    
    if (empty($path)) {
        $path = drupal_get_path('theme', $GLOBALS['theme']);
    }
    
    return $path;
}

/**
 * Includes the a css file, if it exists in the active theme.
 */
function _vanilla_add_css($filename) {
    $path = _vanilla_active_theme_path();

    if (file_exists(DRUPAL_ROOT . "/$path/css/$filename.css")) {
        drupal_add_css("$path/css/$filename.css");
        return "$path/css/$filename.css";
    }
    else {
        return FALSE;
    }
}
