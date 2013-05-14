<?php
/**
 * @file
 * @todo
 */

/**
 * Hooks into webtree_settings_form.
 * Tabs are in group 'webtree_config'
 * Custom Settings tab can be extended using $form['custom_settings'].
 */
function YOURTHEME_webtree_core_settings_alter($form) {
    // add your form settings here
    
    return $form;
}
