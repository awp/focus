<?php
/**
 * @file
 * Provides useful quick & dirty functions for development purposes.
 */

/**
 * FOCUS Print.
 * 
 * A quick & dirty debugger.
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
function fp($v, $keys = FALSE, $array = FALSE) {
    if ($keys) $v = array_keys((array) $v);
    if ($array) return $v;
    
    echo '<pre>'; print_r($v); echo '</pre>';
}

/**
 * FOCUS Print with exit.
 * 
 * A quick & dirty debugger that also exits after executing.
 * 
 *  @param mixed $v
 *   The value to see
 * 
 * @param bool $keys
 *   Output only the keys of $v
 */
function fpx($v, $keys = FALSE) {
    fp($v, $keys);
    exit();
}
