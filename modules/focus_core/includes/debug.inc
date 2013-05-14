<?php
/**
 * @file
 * Quick debuggers for easy use
 */

// set the console key to support multiple console loggings
$_focus_core_console_key = time();

/**
 * Quick & Dirty Debugger
 * 
 * @param mixed $v
 *   The value to see
 * 
 * @param bool $keys
 *   Output only the keys of $v
 * 
 * @param $array
 *   Don't output, rather return as array
 */
function wt($v, $keys = FALSE, $array = FALSE) {
    if ($keys) $v = array_keys((array) $v);
    if ($array) return $v;
    
    echo '<pre>'; print_r($v); echo '</pre>';
}

/**
 * Sets the debugging output to the Drupal Messenger
 * 
 * @param mixed $v
 *   The value to see
 * 
 * @param bool $keys
 *   Output only the keys of $v
 */
function wtm($v, $keys = FALSE) {
    $message = wt($v, $keys, TRUE);
    drupal_set_message(t("<pre>@message</pre>", array('@message' => $message)));
}

/**
 * Kills after output
 * 
 * @param mixed $v
 *   The value to see
 * 
 * @param bool $keys
 *   Output only the keys of $v
 */
function wtx($v, $keys = FALSE) {
    wt($v, $keys);
    die();
}

/**
 * Output to the console
 * 
 * @param mixed $v
 *   The value to see
 * 
 * @param bool $keys
 *   Output only the keys of $v
 */
function wtc($v, $keys = FALSE) {
    global $_focus_core_console_key;
    
    if ($keys) $v = array_keys((array) $v);
    $output = print_r($v, TRUE);
    
    // support multiple instances
    $key = md5($_focus_core_console_key++);
    
    drupal_add_js(array('focus' => array($key => $output)), 'setting');
    $script = "
        jQuery(function($){
            console.log(Drupal.settings.focus['$key']); 
        });
    ";
    drupal_add_js($script, array('type' => 'inline', 'scope' => 'footer'));
}

