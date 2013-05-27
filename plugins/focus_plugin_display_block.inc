<?php
/**
 * @file
 * @todo
 */

/**
 * Returns the date of a datefield relative to the content of the page.
 */
class views_plugin_argument_default_dateline extends views_plugin_argument_default {
    function get_argument() {
        if (!empty($this->view->date_info) && $node = menu_get_object()) {
            foreach ($this->view->date_info->date_fields as $field) {
                $parts = explode('.', $field);
                $key = reset($parts);
                $key = str_replace('field_data_', '', $key);
                if ($key == 'node') $key = array_pop($parts);
                
                if (isset($node->{$key})) {
                    break;
                }
            }
            $node_ = entity_metadata_wrapper('node', $node);

            $value = $node_->{$key}->value();
           
            if (is_numeric($value)) {
                $value = date('c', $value);
            }
            return $value;
        }
    }
}

/**
 * Extends views_handler_field_node
 * Add active-class class to title links during render
 */
class focus_handler_field_node extends views_handler_field_node {
    // TODO: figure out how to add this class to the wrapper element as well
    function render_as_link($alter, $text, $tokens) {
        if (function_exists('menu_get_active_trail')) {
            $menu = menu_get_active_trail();
            
            if (!empty($menu) && !empty($alter['path'])) {
                foreach ($menu as $link) {
                    if (!empty($link['link_path']) && $link['link_path'] != $_GET['q'] && $link['link_path'] == $alter['path']) {
                        $alter['link_attributes']['class'] = 'active-trail';
                    }
                }
            }
        }

        return parent::render_as_link($alter, $text, $tokens);
    }
}

/**
 * Extends views_plugin_display_block
 * Add field where users can assign a class to the views block wrapper
 */ 
class focus_plugin_display_block extends views_plugin_display_block {
    
    function option_definition() {
        $options = parent::option_definition();

        $options['block_css_class'] = array('default' => '', 'translatable' => FALSE);
        $options['block_featured'] = array('default' => 0, 'translatable' => FALSE);

        return $options;
    }
    
    function options_summary(&$categories, &$options) {
        parent::options_summary($categories, $options);

        $block_class = $this->get_option('block_css_class');
        $options['block_css_class'] = array(
            'category' => 'block',
            'title'    => t('Block CSS class'),
            'value'    => ($block_class) ? $block_class : 'None',
        );
        
        $block_featured = $this->get_option('block_featured');
        $options['block_featured'] = array(
            'category' => 'block',
            'title'    => t('Featured Block?'),
            'value'    => ($block_featured) ? 'Yes' : 'No',
        );
    }

    /**
     * Provide the default form for setting options.
     */
    function options_form(&$form, &$form_state) {
        parent::options_form($form, $form_state);

        switch ($form_state['section']) {
            case 'block_css_class':
                $form['#title'] .= t('Block CSS class');
                $form['block_css_class'] = array(
                    '#type' => 'textfield',
                    '#description' => t('Any text entered will appear as an html class on the block wrapper.'),
                    '#default_value' => $this->get_option('block_css_class'),
                );
            break;
            
            case 'block_featured':
                $form['block_featured'] = array(
                    '#type' => 'radios',
                    '#title' => t('Featured Block?'),
                    '#options' => array(1 => 'Yes', 0 => 'No'),
                    '#description' => t('Featured blocks get special treatment within the theme.'),
                    '#default_value' => $this->get_option('block_featured'),
                );
            break;
        }
    }

    /**
     * Perform any necessary changes to the form values prior to storage.
     * There is no need for this function to actually store the data.
     */
    function options_submit(&$form, &$form_state) {
        parent::options_submit($form, $form_state);
        
        switch ($form_state['section']) {
            case 'block_css_class':
                $this->set_option('block_css_class', $form_state['values']['block_css_class']);
            break;
            
            case 'block_featured':
                $this->set_option('block_featured', $form_state['values']['block_featured']);
            break;
        }
    }
    
    /**
     * Validate block_css_class to ensure it is proper html class markup
     */
    function options_validate(&$form, &$form_state) {
        switch ($form_state['section']) {
            case 'block_css_class':
                $block_class = $form_state['values']['block_css_class'];
                if (preg_match('/[^a-zA-Z0-9-_ ]/', $block_class)) {
                    form_error($form['block_css_class'], t('CSS classes must be alphanumeric or dashes only.'));
                }
            break;
        }
    }

}