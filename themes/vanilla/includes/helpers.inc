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
 * Wraps each word of an html string with a tag for styling.
 *
 * @param string $html
 *   The html string which will have each word wrapped.
 *

 * @param array $options
 *   An associative array containing:
 *   - tag: An html element string (i.e. 'span') that will be used as the
 *     wrapping element.
 *   - preserve: A string identical in the same format as $allowable_tags in
 *     strip_tags.  If set, all html tags aside from the preserved tag(s) will
 *     be stripped from the string, allowing for cleaner wrapping of strings.
 */
function _vanilla_html_wrap(&$html, $options = array()) {
    if (isset($options['preserve'])) {
        $html = strip_tags($html, $options['preserve']);
    }

    if (empty($options['tag'])) {
        $options['tag'] = 'span';
    }

    preg_match_all('#\<.*?\>(.*?)\<\/#i', $html, $matches);

    foreach ($matches[1] as $i => $raw) {
        $wrapped = trim(strip_tags($raw));
        _vanilla_string_wrap($wrapped, $options['tag']);
        $html = str_replace($raw, $wrapped, $html);
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
 */
function _vanilla_string_wrap(&$string, $tag = 'span') {
    $parts = explode(' ', $string);
    foreach ($parts as $k => &$part) {
        $part = "<$tag class='part-$k'>$part</$tag>";
    }
    $string = implode(' ', $parts);
}

/**
 * Prepares and statically caches mobile detect class.
 */
function _vanilla_mobile_detect() {
    static $detect;

    if (empty($detect) && module_exists('libraries')) {
        $library = libraries_detect('mobile-detect');
        if (!empty($library['installed'])) {
            libraries_load('mobile-detect');
            $detect = new Mobile_Detect;
        }
    }

    return $detect;
}
