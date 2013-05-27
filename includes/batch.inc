<?php
/**
 * @file
 * Contains Batch API functions for FOCUS profile installation
 */

/**
 * Batch function
 * Sets variables
 * Uses settings.yml to define variables
 * 
 * @param array $context
 *  The batch context for handling results and messaging
 */
function _focus_variables_set(&$context) {
    libraries_load('spyc');
    $settings = Spyc::YAMLLoad(FOCUS_PROFILE_PATH . '/config/settings.yml');
    
    foreach ($settings as $key => $value) {
        variable_set($key, $value);
    }
    
    $context['message'] = st('Set FOCUS Variables');
}

/**
 * Batch function
 * Disables themes
 * 
 * @param array $themes
 *  Theme keys to be disabled
 * 
 * @param array $context
 *  The batch context for handling results and messaging
 */
function _focus_themes_disable($themes, &$context) {
    theme_disable($themes);
    
    $context['message'] = st('Disabled themes: %theme.', array('%theme' => implode(', ', $themes)));
}

/**
 * Batch function
 * Enables themes
 * 
 * @param array $themes
 *  Theme keys to be enabled
 * 
 * @param array $context
 *  The batch context for handling results and messaging
 */
function _focus_themes_enable($themes, &$context) {
    theme_enable($themes);
    
    $context['message'] = st('Enabled themes: %theme.', array('%theme' => implode(', ', $themes)));
}

/**
 * Batch function
 * Disables blocks
 * 
 * @param array $deltas
 *  Block deltas to be disabled
 * 
 * @param array $context
 *  The batch context for handling results and messaging
 */
function _focus_blocks_disable($deltas, &$context) {
    db_update('block')
        ->fields(array('status' => 0, 'region' => -1))
        ->condition('delta', $deltas, 'IN')
        ->execute();

    $context['message'] = st('Disabled blocks: %delta.', array('%delta' => implode(', ', $deltas)));
}

/**
 * Helper function
 * Retrieves FOCUS tools that are set to a specific context
 * 
 * @param string $context
 *  The context name to match against
 * 
 * @return assoc $types
 *  An array of FOCUS tools keyed and valued by their module name
 */
// function _focus_contexts_get($context) {
    // $tools = focus_tools_get();
//     
    // $types = array();
//     
    // foreach ($tools as $tool => $data) {
        // if (in_array($context, variable_get("focus_contexts_$tool", array()))) {
            // $types[$tool] = $tool;
        // }
    // }
//     
    // return $types;
// }

/**
 * Batch function
 * Enables modules for batch processing
 * Copy of _install_module_batch() but installs dependencies as well
 * 
 * @param string $module
 *  Block deltas to be disabled
 *  
 * @param string $module_name
 *  Human Readable Module Name
 * 
 * @param array $context
 *  The batch context for handling results and messaging 
 */
function _focus_module_batch_install($module, $module_name, &$context) {
    module_enable(array($module), TRUE);
    $context['results'][] = $module;
    $context['message'] = st('Installed %module module.', array('%module' => $module_name));
}

/**
 * Batch function
 * Disables and uninstalls modules for batch processing
 * 
 * @param string $module
 *  Module to be disabled
 *  
 * @param string $module_name
 *  Human Readable Module Name
 * 
 * @param array $context
 *  The batch context for handling results and messaging 
 */
function _focus_module_batch_uninstall($module, $module_name, &$context) {
    $placeholders = array('%module' => $module_name);
    if (module_exists($module)) {
        module_disable(array($module));
        drupal_uninstall_modules(array($module));
        $context['message'] = st('Uninstalled %module module.', $placeholders);
    }
    else {
        $context['message'] = st('%module not installed, no need to uninstall.', $placeholders);
    }

    $context['results'][] = $module;
}
