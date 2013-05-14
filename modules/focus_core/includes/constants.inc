<?php
/**
 * @file
 * Module constant definitions
 */

if (!defined('FOCUS_CORE_PATH'))
    define('FOCUS_CORE_PATH', drupal_get_path('module', 'focus_core'));

if (!defined('FOCUS_CORE_CONFIG_PATH'))
    define('FOCUS_CORE_CONFIG_PATH', FOCUS_CORE_PATH . '/config');

if (!defined('FOCUS_CORE_MODULE_PATH'))
    define('FOCUS_CORE_MODULE_PATH', FOCUS_CORE_PATH . '/modules');

if (!defined('FOCUS_CORE_CONFIG'))
    define('FOCUS_CORE_CONFIG', 'admin/focus/config');

if (!defined('FOCUS_FIELD_CREATED'))
    define('FOCUS_FIELD_CREATED', 1);

if (!defined('FOCUS_FIELD_UPDATED'))
    define('FOCUS_FIELD_UPDATED', 2);
