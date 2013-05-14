<?php
/**
 * @file
 * Module helper functions.
 */

/**
 * Checks for existing file before trying YAMLLoad.
 * 
 * @param {String} $file
 *  A path to a yaml file to load.
 */
function _focus_tools_yaml_load($file) {
    return (file_exists($file))
        ? Spyc::YAMLLoad($file)
        : FALSE;
}

/**
 * Adds default node values to a node for less verbose node creation.
 */
function focus_tools_node_prepare($node) {
    $defaults = _focus_tools_yaml_load(FOCUS_TOOLS_PATH . '/config/defaults/content.yml');
    foreach ($defaults as $key => $value) {
        if (empty($node->{$key})) {
            $node->{$key} = $value;
        }
    }
}
 
/**
 * Provides a merged array of default bundle settings and the module requested bundle settings
 * 
 * @param string $module 
 *  The module that contains the bundle
 */
function _focus_tools_bundle_get($module) {
    $path = drupal_get_path('module', $module);
    
    if ($settings = _focus_tools_yaml_load("$path/config/bundle.yml")) {
        $defaults = Spyc::YAMLLoad(FOCUS_TOOLS_PATH . '/config/defaults/bundle.yml');
        return array_merge($defaults, (array) $settings);
    }
    
    return FALSE;
}

/**
 * @todo
 */
function _focus_tools_field_group_get($module) {
    $path = drupal_get_path('module', $module);
    
    if ($settings = _focus_tools_yaml_load("$path/config/field_groups.yml")) {
    
        $defaults = Spyc::YAMLLoad(FOCUS_TOOLS_PATH . '/config/defaults/field_groups.yml');
        
        $groups = array();
        $i = 0;
        
        foreach ($settings as $group_name => $values) {
            $raw = (object) array_merge_recursive($defaults, (array) $values);
            $raw->identifier = "{$group_name}|{$raw->entity_type}|{$module}|{$raw->mode}";
            $raw->group_name = $group_name;
            $raw->bundle = $module;
            $raw->data['weight'] = $i++;
            
            if (is_array($raw->entity_type)) $raw->entity_type = array_pop($raw->entity_type);
            
            $groups[$raw->identifier] = $raw;
            
            // taxonomy term name and description aren't managed via the field api
            if ($raw->entity_type == 'taxonomy_term' && !empty($raw->data['children'])) {
                if (in_array('name', $raw->data['children']) || in_array('description', $raw->data['children'])) {
                    $settings = variable_get("field_bundle_settings_taxonomy_term__$module", array('extra_fields' => array('form' => array())));
                    $extra_fields = $settings['extra_fields']['form'];
                    $extra_fields['path'] = array('weight' => 50);
                    
                    foreach ($raw->data['children'] as $key => $child) {
                        if ($child != 'name' && $child != 'description') continue;
                        $extra_fields[$child] = array('weight' => $key);
                    }
                    
                    $settings['extra_fields']['form'] = $extra_fields;
                    variable_set("field_bundle_settings_taxonomy_term__$module", $settings);
                }
            }
        }
        
        return $groups;
    }

    return FALSE;
}

/**
 * Provides a merged array of default field instance settings and the module field instance settings
 * 
 * @param {String} $module
 *  The module that contains the field instance
 * 
 * @param {String} $field 
 *  The field on which the instance is built
 */
function _focus_tools_field_instance_get($module, $field) {
    $path = drupal_get_path('module', $module);
    
    if ($settings = _focus_tools_yaml_load("$path/config/field_instances.yml")) {
        $fields   = _focus_fields_get();
        $defaults = Spyc::YAMLLoad(FOCUS_TOOLS_PATH . '/config/defaults/field_instance.yml');
        
        if (empty($fields[$field])) return FALSE;
        
        $defaults = array_merge($fields[$field], $defaults);
        
        return array_merge($defaults, (array) $settings[$field]);
    }
    
    return FALSE;
}

/**
 * Generic updator of field instances for submodules
 * 
 * @param string $module
 *  The module bundle on which to create field instances
 */
function _focus_tools_field_instances_update($module) {
    _focus_tools_field_instances_create($module, TRUE);
    drupal_set_message(t('FOCUS Field Instances Updated for @module.', array("@module" => $module)));
}

/**
 * Generic creator of field instances for submodules
 * 
 * @param string $module
 *  The module bundle on which to create field instances
 */
function _focus_tools_field_instances_create($module, $rebuild = FALSE) {
    $path = drupal_get_path('module', $module);
    
    if ($fields = _focus_tools_yaml_load("$path/config/field_instances.yml")) {
        node_types_rebuild();
        $types = node_type_get_types();
        
        // parse the yaml file for fields to add to this bundle
        foreach ($fields as $field => $instance) {
            // The body field is different than other fields and has its own create handler
            // This inherently makes updating need to be more explicit
            if ($field == 'body') {
                $label = (empty($instance['label'])) ? 'Body' : $instance['label'];
                
                if ($rebuild && $body = field_info_instance('node', 'body', $module)) {
                    $body['label'] = $label;
                    field_update_instance($body);
                }
                else {
                    node_add_body_field($types[$module], $label);
                }
                
                continue;
            }
            
            _focus_tools_field_instance_create($module, $field, $rebuild);
        }
    }
}

/**
 * Generic creator of single field instance for tools.
 * 
 * @param {String} $module
 *  The module bundle on which to attach this instance 
 * 
 * @param {String} $field
 *  The field of which to create an instance
 */
function _focus_tools_field_instance_create($module, $field, $rebuild = FALSE) {
    if ($instance = _focus_tools_field_instance_get($module, $field)) {
    
        $instance['bundle']     = (empty($instance['bundle'])) ? $module : $instance['bundle'];
        $instance['field_name'] = $field;
        
        // if the field already has an instance on this entity_type, do nothing
        if (field_info_instance($instance['entity_type'], $field, $module)) {
            if ($rebuild) field_update_instance($instance);
            return;
        }
        
        field_create_instance($instance);
        
    }
}

/**
 * Generic deleter of field instances for submodules
 * 
 * @param {String} $module
 *  The module bundle from which to purge all field instances
 */
function _focus_tools_field_instances_delete($module) {
    $path = drupal_get_path('module', $module);

    if ($fields = _focus_tools_yaml_load("$path/config/field_instances.yml")) {
        foreach ($fields as $field => $instance) {
            _focus_tools_field_instance_delete($module, $field);
        }   
    }

    return TRUE;
}

/**
 * Generic deleter of single field instance for submodules
 * 
 * @param {String} $module
 *  The module bundle from which to purge this field instance
 * 
 * @param {String} $field
 *  The field of which to delete the instance
 */
function _focus_tools_field_instance_delete($module, $field) {
    if ($instance = _focus_tools_field_instance_get($module, $field)) {
        $instance['bundle']     = $module;
        $instance['field_name'] = $field;
        
        if (field_info_instance($instance['entity_type'], $field, $module)) {
            field_delete_instance($instance, FALSE); // don't do field cleanup - these fields are made available by FOCUS core for future use
        }
        
        field_purge_batch(100);
    }
}

/**
 * @todo
 */
function _focus_tools_taxonomy_create($tool) {
    $path = drupal_get_path('module', $tool);
    
    if ($settings = _focus_tools_yaml_load("$path/config/taxonomy.yml")) {
        $defaults = Spyc::YAMLLoad(FOCUS_TOOLS_PATH . '/config/defaults/taxonomy.yml');
        $vocab = array_merge($defaults, (array) $settings);
        taxonomy_vocabulary_save((object) $vocab);
    }
}

/**
 * Parses settings file for a node module and sets the Drapal variable(s) accordingly
 * 
 * @param string $tool
 *  The node module for which to parse settings
 */
function _focus_tools_default_settings($tool) {
    $path = drupal_get_path('module', $tool);
    if ($settings = _focus_tools_settings_get($tool)) {
        foreach ($settings as $setting => $value) {
            variable_set($setting . '_' . $tool, $value);
        }
    }
}

/**
 * Provides a merged array of default extra settings and the module requested extra settings
 * 
 * @param {String} $module 
 *  The module that contains the bundle
 * 
 * @return {Mixed}
 *  Array of settings or
 *  FALSE if no settings specified
 */
function _focus_tools_settings_get($module) {
    $path = drupal_get_path('module', $module);
    
    if ($settings = _focus_tools_yaml_load("$path/config/settings.yml")) {
        $defaults = Spyc::YAMLLoad(FOCUS_TOOLS_PATH . '/config/defaults/settings.yml');
        return array_merge($defaults, (array) $settings);
    }
    
    return FALSE;
}

/**
 * Generic structure settings
 * Sets allowed children content types on a parent content type
 * 
 * @param string $module
 *  The parent content type to add children
 */
function _focus_tools_allow_as_child($module) {
    $path = drupal_get_path('module', $module);
    
    if ($parents = _focus_tools_yaml_load("$path/config/parents.yml")) {
        $allowed = array();
        
        foreach ($parents as $parent) {
            $parent_children = variable_get("focus_structure_children_$parent", array());
            $parent_children[$module] = $module;
            variable_set("focus_structure_children_$parent", $parent_children);
        }
    }
}

/**
 * Generic installer
 * Aggregates helper functions during module install for clearer workflow
 * 
 * @param string $tool
 *  The module being installed
 */
function _focus_tools_tool_install($tool) {
    _focus_fields_create();
    _focus_tools_field_instances_create($tool);
    _focus_tools_default_settings($tool);
    _focus_tools_allow_as_child($tool);
}

/**
 * Create a generic default field instance array
 * 
 * @param string $name
 *  The human-readable name of the field (will be the label)
 * @param array $field
 *  An array typically built for field_create_field() but with an added 'widget' key
 * 
 * @return array
 *  The default field instance array for use with field_create_instance()
 */
function _focus_tools_default_field_instance_create($field_name, $field) {
    return array(
        'field_name' => $field_name,
        'entity_type' => (empty($field['entity_type'])) ? 'node' : $field['entity_type'],
        'bundle' => (empty($field['bundle'])) ? 'focus' : $field['bundle'],
        'label' => $field['label'],
        'widget' => (empty($field['widget'])) ? array() : $field['widget'],
        'settings' => (empty($field['settings'])) ? array() : $field['settings'],
    );
}

/**
 * Reprocesses content type fields and updates content types with any changes
 */
function _focus_fields_rebuild($form, $form_state) {
    // First, handle updating of fields
    _focus_fields_update(TRUE);
    
    // If no content types need an update, we're done
    if (empty($form_state['values']['types']) && empty($form_state['values']['vocabs'])) return;
    
    if (empty($form_state['values']['types'])) $form_state['values']['types'] = array();
    if (empty($form_state['values']['vocabs'])) $form_state['values']['vocabs'] = array();
    
    $values = array_merge($form_state['values']['types'], $form_state['values']['vocabs']);
    
    // Otherwise we need to update the field instances on selected content types
    foreach ($values as $type => $rebuild) {
        if (!$rebuild) continue;
        
        _focus_tools_field_instances_update($type);
    }
    
    cache_clear_all('*', 'cache_menu', TRUE);
    cache_clear_all('*', 'cache_admin_menu', TRUE);
}

/**
 * Generic abstraction function
 * Updates FOCUS core fields
 */
function _focus_fields_update() {
    _focus_fields_create(TRUE);
    drupal_set_message(t('FOCUS Fields Updated.'));
}

/**
 * @todo
 */
function _focus_fields_get() {
    $defaults = Spyc::YAMLLoad(FOCUS_TOOLS_PATH . '/config/fields.yml');
    
    foreach (module_implements('focus_fields') as $module) {
        foreach (module_invoke($module, 'focus_fields') as $fieldmodule) {
            $path = drupal_get_path('module', $fieldmodule);
            if ($fields = _focus_tools_yaml_load("$path/config/fields.yml")) {
                $defaults = array_merge($defaults, $fields);
            }
        }
    }
    
    return $defaults;
}

/**
 * Generic creator of core fields with option to update existing fields
 * 
 * @param bool $update
 *  If field(s) exist, update them
 */
function _focus_fields_create($update = FALSE) {
    $fields = _focus_fields_get();
    $created = variable_get('focus_created_fields', array());
    
    // create focus fields & default instances
    foreach ($fields as $field_name => $field) {
        
        $field['field_name'] = $field_name;
        $instance = _focus_tools_default_field_instance_create($field_name, $field);
        
        // if field already exists, update if requested
        if ($existing = field_info_field($field_name)) {
            if (!$update) continue;
            
            $instance = array_merge($existing, $instance);
            
            field_update_field($field);
            field_update_instance($instance);
            
            $created[$field_name] = FOCUS_FIELD_UPDATED;
        }
        else {
            field_create_field($field);
            field_create_instance($instance); // create a default instance to make available as 'existing fields' option
            
            $created[$field_name] = FOCUS_FIELD_CREATED;
        }
        
    }
    
    // track the fields that were created by focus to prevent accidental removal of pre-existing fields by uninstall
    variable_set('focus_created_fields', $created);
}
