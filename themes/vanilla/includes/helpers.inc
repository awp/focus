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
        drupal_add_css("$path/css/$filename.css", array('group' => CSS_THEME));
        return "$path/css/$filename.css";
    }
    else {
        return FALSE;
    }
}

/**
 * Wraps each word of a string with a tag for styling.
 *
 * @param string $string
 *   The string which will have each word wrapped.
 *
 * @param string $tag
 *   An html tag to wrap each word in.
 *
 * @return string
 *   The original string with each word wrapped in an html tag.
 */
function _vanilla_html_wrap(&$string, $tag = 'span') {
    $raw = strip_tags($string);
    $parts = explode(' ', $raw);
    foreach ($parts as $k => &$part) {
        $part = "<$tag class='part-$k'>$part</$tag>";
    }
    $parts = implode('', $parts);
    $string = str_replace($raw, $parts, $string);
}
