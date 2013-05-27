<?php
/**
 * @file
 * Defines context plugin classes.
 */

/**
 * Expose menu entry to define a context.
 */
class focus_contexts_menu_context_condition extends context_condition_node {
    
    function condition_values() {
        return menu_get_menus(TRUE);
    }

    function options_form($context) {
        return array();
    }

    function execute($node, $op) {
        if ($menu_name = _focus_contexts_menu_name_get($node)) {
            foreach ($this->get_contexts() as $context) {
                if (!empty($context->conditions['focus_contexts_menu']['values'])) {
                    $values = $context->conditions['focus_contexts_menu']['values'];
                    if (isset($values[$menu_name])) {
                        $this->condition_met($context, $menu_name);
                    }
                }
            }
        }
    }
}
