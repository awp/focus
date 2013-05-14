<?php
/**
 * @file
 * Module helper functions.
 */

/**
 * @todo
 */
function _focus_core_ckeditor_settings_set() {
    $formats  = Spyc::YAMLLoad(FOCUS_CORE_CONFIG_PATH . '/ckeditor.yml');
    $defaults = Spyc::YAMLLoad(FOCUS_CORE_CONFIG_PATH . '/defaults/ckeditor.yml');
    
    foreach ($formats as $format => $values) {
        $filter_format = (object) $values['format'];
        $filter_format->format = $format;
        foreach ($filter_format->filters as $key => $filter) {
            $filter_format->filters[$filter] = array('status' => 1);
            unset($filter_format->filters[$key]);
        }
        filter_format_save($filter_format);
        
        foreach ($values['roles'] as $role) {
            $role = user_role_load_by_name($role); 
            if (isset($role->rid)) user_role_change_permissions($role->rid, array("use text format $format" => 1));
        }
        
        if (empty($values['settings'])) $settings = $defaults; 
        else $settings = array_merge($defaults, $values['settings']);
        
        $settings['block_formats'] = implode(',', $settings['block_formats']);
        $settings['access_pages'] = implode("\n", $settings['access_pages']);
        
        db_merge('wysiwyg')
            ->key(array('format' => $format))
            ->fields(array(
                'editor' => 'ckeditor',
                'settings' => serialize($settings),
            ))
            ->execute();
    }
}

/**
 * @todo
 */
function _focus_core_roles_create() {
    $roles = Spyc::YAMLLoad(FOCUS_CORE_CONFIG_PATH . '/roles.yml');
    
    $all = user_permission_get_modules();
    foreach ($all as &$one) {
        $one = TRUE;
    }
        
    foreach ($roles as $role_name => $permissions) {
        // create new role
        if (!user_role_load_by_name($role_name)) {
            $role = new stdClass;
            $role->name = $role_name;
            $status = user_role_save($role);
        }
        
        if (empty($permissions)) continue;
        
        // manage permissions
        if ($role = user_role_load_by_name($role_name)) {
            if ($permissions == '*') $permissions = $all;
            
            user_role_change_permissions($role->rid, $permissions);
        }
    }
}
