<?php
/**
 * @file
 * Contains functions for creating a subtheme.
 * 
 * These functions were inspired by work done by the omega_tools module.
 * @see http://drupal.org/project/omega_tools
 */

/**
 * Copies a starterkit and moves it into place.
 * 
 * @param array $values
 *   An associative array of values for the new theme including:
 *   - name: The human readable name of the new theme.
 *   - machine_name: The machine name of the new theme.
 *   - description: The description of the new theme.
 */
function focus_subtheme_create($values) {
    
    $subtheme = new stdClass;
    $subtheme->new = TRUE;
    $subtheme->automated = 1;
    $subtheme->name = $values['name'];
    $subtheme->machine_name = $values['machine_name'];
    $subtheme->description = $values['description'];
    $subtheme->starterkit = 'prime';
    $subtheme->base = 'vanilla';
    $subtheme->destination = 'sites/default/themes/' . $subtheme->machine_name;
    $subtheme->path = 'temporary://webtree/' . $subtheme->machine_name . '-' . substr(hash('sha256', serialize($subtheme) . microtime()), 0, 8);
    
    if (is_dir($subtheme->path)) {
        file_unmanaged_delete_recursive($subtheme->path);
    }
    
    if (!file_prepare_directory($subtheme->path, FILE_CREATE_DIRECTORY)) {
        drupal_set_message(t('WebTree could not create the directory %dir.', array('%dir' => $subtheme->path)), 'error');
        watchdog('WebTree Install', t('WebTree could not create the directory %dir.', array('%dir' => $subtheme->path)), array(), WATCHDOG_ERROR);        

        return FALSE;
    }

    if (!focus_copy_recursive(drupal_get_path('theme', $subtheme->starterkit), $subtheme->path)) {
        $themes = list_themes();
        
        drupal_set_message(t('WebTree could not copy the starterkit %starterkit.', array('%starterkit' => $themes[$subtheme->starterkit]->info['name'])), 'error');
        watchdog('WebTree Install', t('WebTree could not copy the starterkit %starterkit.', array('%starterkit' => $themes[$subtheme->starterkit]->info['name'])), array(), WATCHDOG_ERROR);        

        return FALSE;
    }
    
    $subtheme->info = drupal_parse_info_file($subtheme->path . '/' . $subtheme->starterkit . '.info');
    
    file_unmanaged_delete($subtheme->path . '/' . $subtheme->starterkit . '.info');

    $subtheme->info = drupal_parse_info_file(drupal_get_path('theme', $subtheme->base) . '/' . $subtheme->base . '.info');
    $subtheme->info['name'] = $subtheme->name;
    $subtheme->info['description'] = $subtheme->description;
    $subtheme->info['base theme'] = $subtheme->base;
    $subtheme->info['engine'] = 'phptemplate';
    $subtheme->info['core'] = DRUPAL_CORE_COMPATIBILITY;
    $subtheme->info['version'] = '1.0';
    $subtheme->info['screenshot'] = 'screenshot.png';
    unset($subtheme->info['hidden'], $subtheme->info['locked'], $subtheme->info['project'], $subtheme->info['datestamp']);

    focus_write_info_file($subtheme->machine_name, $subtheme->info, $subtheme->path);
    focus_rewrite_recursive($subtheme->path, 'prime', $subtheme->machine_name, str_replace('_', '-', $subtheme->machine_name));
    focus_move($subtheme->path, $subtheme->destination);
    drupal_set_message(t('You have successfully created the theme %name.', array('%name' => $subtheme->name)));

    drupal_theme_rebuild();
    system_rebuild_theme_data();

    theme_enable(array($subtheme->machine_name));
    variable_set('theme_default', $subtheme->machine_name);
    drupal_set_message(t('%name is now the default theme.', array('%name' => $subtheme->name)));

    return TRUE;
    
}

/**
 * @todo
 */
function focus_copy_recursive($source, $destination) {
    if (is_dir($source)) {
        if (!file_prepare_directory($destination, FILE_CREATE_DIRECTORY)) {
            return FALSE;
        }
        
        $directory = dir($source);
        
        while (FALSE !== ($read = $directory->read())) {
            if ($read != '.' && $read != '..' ) {            
                if (!focus_copy_recursive($source . '/' . $read, $destination . '/' . $read)) {
                    return FALSE;
                }
            }
        }
        
        $directory->close();
    } 
    else {
        file_unmanaged_copy($source, $destination);
    }
    
    return TRUE;
}

/**
 * @todo
 */
function focus_write_info_file($name, $info, $destination = NULL) {
    $destination = isset($destination) ? $destination : drupal_get_path('theme', $name);
    
    if (!empty($destination)) {
        return file_unmanaged_save_data(focus_build_info_file($info), $destination . '/' . $name . '.info', FILE_EXISTS_REPLACE);
    }
    
    return FALSE;
}

/**
 * @todo
 */
function focus_build_info_file($array, $prefix = FALSE) {
    $info = '';

    foreach ($array as $key => $value) {
        if (is_array($value)) {
            $info .= focus_build_info_file($value, (!$prefix ? $key : "{$prefix}[{$key}]"));
        }
        else {
            if (is_numeric($key)) {
                $info .= $prefix ? ("{$prefix}[]") : $key;
            }
            else {
                $info .= $prefix ? ("{$prefix}[{$key}]") : $key;
            }
            $info .= " = '" . str_replace("'", "\'", $value) . "'\n";
        }
    }

    return $info;
}

/**
 * @todo
 */
function focus_rewrite_recursive($path, $search, $replace, $rename) {
    if ($path !== ($new = str_replace($search, $rename, $path))) {
        if (!$path = file_unmanaged_move($path, $new, FILE_EXISTS_REPLACE)) {
            return FALSE;
        };
    }
     
    if (is_dir($path)) {
        $directory = dir($path);
        
        while (FALSE !== ($read = $directory->read())) {
            if ($read != '.' && $read != '..' ) {
                if (!focus_rewrite_recursive($path . '/' . $read, $search, $replace, $rename)) {
                    return FALSE;
                }
            }
        }
        
        $directory->close();
    }
    else {
        focus_replace_contents($path, $search, $replace);
    }
    
    return TRUE;
}

/**
 * @todo
 */
function focus_replace_contents($file, $search, $replace) {
    if (is_file($file) && filesize($file) > 0) {
        $before = file_get_contents($file);

        if ($before != ($after = str_replace($search, $replace, $before))) {
            file_unmanaged_save_data($after, $file, FILE_EXISTS_REPLACE);
        }
    }
}

/**
 * @todo
 */
function focus_move($source, $destination) {
    if (focus_copy_recursive($source, $destination)) { 
        file_unmanaged_delete_recursive($source);
    
        return $destination;
    }
    
    return FALSE;
}