<?php
/**
 * @file
 * @todo
 */
 
if (!defined('FOCUS_PROFILE_PATH'))
    define('FOCUS_PROFILE_PATH', drupal_get_path('profile', 'focus'));

    if (!defined('FOCUS_CONFIG_PATH'))
    define('FOCUS_CONFIG_PATH', FOCUS_PROFILE_PATH . '/config');

if (!defined('FOCUS_MODULE_PATH'))
    define('FOCUS_MODULE_PATH', FOCUS_PROFILE_PATH . '/modules');

if (!defined('FOCUS_CONFIG'))
    define('FOCUS_CONFIG', 'admin/focus/config');