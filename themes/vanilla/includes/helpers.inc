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

    $words = explode('<', $html);
    $i = 0;

    foreach ($words as &$word) {
        if (empty($word)) {
            continue;
        }

        if (FALSE !== strpos($word, '>')) {
            $parts = explode('>', $word);
            // $parts[1] should be the html-wrapped string.
            if (!empty($parts[1])) {
                _vanilla_string_wrap($parts[1], $options['tag'], $i);
            }
            $word = implode('>', $parts);
        }
    }
    $html = implode('<', $words);
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
 * @param int $start
 *   An index number from which to resume part class indexing.
 */
function _vanilla_string_wrap(&$string, $tag = 'span', &$start = FALSE) {
    $parts = explode(' ', $string);
    if (count($parts) > 1) {
        foreach ($parts as $k => &$part) {
            // Don't wrap empty spaces...
            if (empty($part)) {
                continue;
            }

            if (FALSE !== $start) {
                $k = $start++;
            }

            $part = "<$tag class='part-$k'>$part</$tag>";
        }
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
