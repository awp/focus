<?php
/**
 * @file
 * Contains Batch API functions for WebTree profile installation
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
    $settings = Spyc::YAMLLoad(WEBTREE_PROFILE_PATH . '/config/settings.yml'); // Spyc is integrated by WebTree Core
    
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
 * Batch function
 * Creates contexts from settings in contexts.yml
 * 
 * @param array $context
 *  The batch context for handling results and messaging
 */
function _focus_contexts_create(&$context) {
    $contexts = Spyc::YAMLLoad(WEBTREE_PROFILE_PATH.'/config/contexts.yml');
    
    ctools_include('export');
    
    foreach ($contexts as $name => $data) {
        $new = (object) $data;
        $new->name = $name;
        $new->disabled = FALSE;
        $new->api_version = 3;
        $new->export_type = FALSE;
        
        if (!empty($new->conditions['node']) && is_string($new->conditions['node']['values']) && strpos($new->conditions['node']['values'], 'php')) {
            $parse = explode(':', $new->conditions['node']['values']);
            $fn = array_pop($parse);
            
            $new->conditions['node']['values'] = $fn($name);
        }
        
        ctools_export_crud_save('context', $new);
        unset($new);
    }
    
    $context['message'] = st('Created contexts: %contexts', array('%contexts' => implode(', ', array_keys($contexts))));
}

/**
 * Batch function
 * Creates deltas from settings in deltas.yml
 * 
 * @param array $context
 *  The batch context for handling results and messaging
 */
function _focus_deltas_create(&$context) {
    $deltas = Spyc::YAMLLoad(WEBTREE_PROFILE_PATH.'/config/deltas.yml');
    $theme  = variable_get('theme_default', 'bartik');
    
    ctools_include('export');
    
    foreach ($deltas as $machine_name => $data) {
        $new = (object) $data;
        $new->disabled = FALSE;
        $new->api_version = 3;
        $new->export_type = FALSE;
        $new->theme = $theme;
        $new->machine_name = $machine_name;
        
        ctools_export_crud_save('delta', $new);
        unset($new);
    }
    
    $context['message'] = st('Created deltas: %delta', array('%delta' => implode(', ', array_keys($deltas))));
}

/**
 * Helper function
 * Retrieves WebTree tools that are set to a specific context
 * 
 * @param string $context
 *  The context name to match against
 * 
 * @return assoc $types
 *  An array of WebTree tools keyed and valued by their module name
 */
function _focus_contexts_get($context) {
    $tools = focus_tools_get();
    
    $types = array();
    
    foreach ($tools as $tool => $data) {
        if (in_array($context, variable_get("focus_contexts_$tool", array()))) {
            $types[$tool] = $tool;
        }
    }
    
    return $types;
}

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
    module_disable(array($module));
    drupal_uninstall_modules(array($module));
    $context['results'][] = $module;
    $context['message'] = st('Uninstalled %module module.', array('%module' => $module_name));
}
