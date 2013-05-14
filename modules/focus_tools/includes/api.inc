<?php
/**
 * @file
 * @todo
 */

/**
 * Generic content type (node) installer
 * Aggregates helper functions during module install for clearer workflow
 * 
 * @param string $tool
 *  The node module being installed
 */
function focus_tools_content_type_install($tool) {
    _focus_tools_tool_install($tool);
}

/**
 * Generic taxonomy installer
 * Aggregates helper functions during module install for clearer workflow
 * 
 * @param string $tool
 *  The taxonomy module being installed
 */
function focus_tools_taxonomy_install($tool) {
    _focus_tools_taxonomy_create($tool);
    _focus_tools_tool_install($tool);
}

/**
 * Retrieves all node modules
 * 
 * @return assoc
 *  A simple associative array of child modules available to FOCUS Core
 */
function focus_tools_get() {
    global $base_path;
    
    $path  = drupal_realpath('.') . '/' . FOCUS_TOOLS_MODULE_PATH;
    $tools = array();
    $modules = system_rebuild_module_data();
    
    if ($handle = opendir($path)) {
        while (FALSE !== ($entry = readdir($handle))) {
            if ($entry != '.' && $entry != '..') {
                $tools[$entry] = $modules[$entry];
            }
        }
        
        closedir($handle);
    }
    
    ksort($tools);
    
    return $tools;
}

/**
 * @todo
 */
function focus_tools_types_get() {
    $all   = focus_tools_get();
    $tools = module_implements('focus_content_type');
    
    $types = array();
    
    foreach ($tools as $type) {
        if (variable_get("focus_structure_enabled_$type", FALSE)) {
            $types[$type] = $all[$type];
        }
    }
    
    return $types;
}

/**
 * Implements hook_modules_installed().
 */
function focus_tools_modules_installed($modules) {
    $tools = focus_tools_get();
    $types = module_implements('focus_content_type');
    $types = array_keys($types);
    
    foreach ($modules as $module) {
        if (empty($tools[$module])) continue;
        
        if (isset($types[$module])) {
            // content types
            focus_tools_content_type_install($module);
        }
        else {
            // assume taxonomy, for now
            focus_tools_taxonomy_install($module);
        }
    }
}

/**
 * Implements hook_modules_uninstalled().
 */
function focus_tools_modules_uninstalled($modules) {
    $tools = focus_tools_get();
    
    foreach ($modules as $module) {
        if (empty($tools[$module])) continue;
        
        _focus_tools_field_instances_delete($module);
    }
}
