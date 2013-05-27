<?php
/**
 * @file
 * Contains functions specific to the views api.
 */

/**
 * Implements hook_views_data_alter().
 */
function focus_views_data_alter(&$data) {
    // Use our custom handler to tweak the class based on active trail.
    $data['node']['title']['field']['handler'] = 'focus_handler_field_node';
    
    // Have date arguments use our custom handler.
    $tables = date_views_base_tables();
    foreach ($tables as $base_table => $entity) {
        $data[$base_table]['date_argument']['argument']['handler'] = 'focus_date_argument_handler';
    }
}

/**
 * Implements hook_field_views_data_alter().
 */
function focus_field_views_data_alter(&$result, $field, $module) {
    // Have date arguments use our custom handler.
    if ($module == 'date') {
        foreach ($result as $table => $data) {
            foreach ($data as $column => $value) {
                if (array_key_exists('argument', $value)) {
                    $result[$table][$column]['argument']['handler'] = 'focus_date_argument_handler';
                }
            }
        }
    }
}

/**
 * Implements hook_views_plugins().
 */
function focus_views_plugins() {
    $plugins['argument default'] = array(
        'focus_date_plugin' => array(
            'title' => t('Date Field of the Content ID from URL'), 
            'handler' => 'views_plugin_argument_default_dateline',
        ),
    );
    
    return $plugins;
}

/**
 * Implements hook_views_plugins_alter().
 */
function focus_views_plugins_alter(&$plugins) {
    // Use our custom handler to add a field that enables adding of block classes.
    $plugins['display']['block']['handler'] = 'focus_plugin_display_block';
}

/**
 * Extends date_views_argument_handler to add compare 
 */
class focus_date_argument_handler extends date_views_argument_handler{
    
    /**
     * Set up compare option.
     */
    function option_definition() {
        $options = parent::option_definition();
        $options['compare'] = array('default' => '=');
        return $options;
    }
  
    /**
     * Implement compare option into option form.
     */
    function options_form(&$form, &$form_state) {
        parent::options_form($form, $form_state);

        $options = array(
            '!' => t('Any'),
            '=' => t('Equal'),
            '!=' => t('Not Equal'),
            '>' => t('Greater Than'),
            '>=' => t('Greater Than or Equal'),
            '<' => t('Less Than'),
            '<=' => t('Less Than or Equal'),
        );

        $form['compare'] = array(
            '#type' => 'select',
            '#title' => t('Relationship to this date'),
            '#default_value' => $this->options['compare'],
            '#options' => $options,
            '#description' => t('@todo'), // TODO
        );

        $options = $this->date_handler->date_parts();
        $options += array('week' => t('Week', array(), array('context' => 'datetime')));
        $form['granularity'] = array(
            '#title' => t('Granularity'),
            '#type' => 'radios',
            '#options' => $options,
            '#default_value' => $this->options['granularity'],
            '#multiple' => TRUE,
            '#description' => t("Select the type of date value to be used in defaults, summaries, and navigation. For example, a granularity of 'month' will set the default date to the current month, summarize by month in summary views, and link to the next and previous month when using date navigation."),
        );
    }
  
    /**
     * date_views_argument_handler.inc
     * @see date_views_argument_handler_simple::query
     */ 
    function doQuery($group_by) {
          
        // See if we need to reset granularity based on an argument value.
        // Make sure we don't try to reset to some bogus value if someone has typed in an unexpected argument.
        $granularity = $this->date_handler->arg_granularity($this->argument);
        if (!empty($granularity)) {
            $this->date_handler->granularity = $granularity;
            $this->format = $this->date_handler->views_formats($this->date_handler->granularity, 'display');
            $this->sql_format = $this->date_handler->views_formats($this->date_handler->granularity, 'sql');
        }
        $this->granularity = $this->date_handler->granularity;
        $this->ensure_my_table();
        $group = !empty($this->options['date_group']) ? $this->options['date_group'] : 0;
    
        // If requested, add the delta field to the view so we can later find the value that matched our query.
        if (!empty($this->options['add_delta']) && (substr($this->real_field, -6) == '_value' || substr($this->real_field, -7) == '_value2')) {
            $this->query->add_field($this->table_alias, 'delta');
            $real_field_name = str_replace(array('_value', '_value2'), '', $this->real_field);
            $this->query->add_field($this->table_alias, 'entity_id', 'date_id_' . $real_field_name);
            $this->query->add_field($this->table_alias, 'delta', 'date_delta_' . $real_field_name);
        }
    
        $format = $this->date_handler->granularity == 'week' ? DATE_FORMAT_DATETIME : $this->sql_format;
        $view_min = date_format($this->min_date, $format);
        $view_max = date_format($this->max_date, $format);
        $view_min_placeholder = $this->placeholder();
        $view_max_placeholder = $this->placeholder();
        $this->date_handler->placeholders = array($view_min_placeholder => $view_min, $view_max_placeholder => $view_max);
        
        // Only use the compare option if we're not doing a from/to query.
        if (!empty($this->options['use_fromto'])) {
            // The simple case, match the field to the view range.
            $field = $this->date_handler->sql_field($this->table_alias . '.' . $this->real_field, NULL, $this->min_date);
            $field = $this->date_handler->sql_format($format, $field);

            switch ($this->options['compare']) {
                case '<': # nobreak;
                case '<=':
                    $this->query->add_where_expression($group, "$field {$this->options['compare']} $view_min_placeholder", array($view_min_placeholder => $view_min));
                    break;
                case '>': # nobreak;
                case '>=':
                    $this->query->add_where_expression($group, "$field {$this->options['compare']} $view_min_placeholder", array($view_min_placeholder => $view_min));
                    break;
                case '!=':
                    $this->query->add_where_expression($group, "$field != $view_min_placeholder AND $field != $view_max_placeholder", array($view_min_placeholder => $view_min, $view_max_placeholder => $view_max));
                    break;
                case '=': # nobreak;
                default:
                    $this->query->add_where_expression($group, "$field >= $view_min_placeholder AND $field <= $view_max_placeholder", array($view_min_placeholder => $view_min, $view_max_placeholder => $view_max));
            }
        }
        
    }
  
    /**
     * Set up the query for this argument.
     *
     * The argument sent may be found at $this->argument.
     * date_views_argument_handler.inc
     * @see: date_views_argument_handler::query
     */
    function query($group_by = FALSE) {
        
        if ($this->date_forbid()) {
          // return;
        }
      
        if ($this->options['compare'] == '=') return parent::query($group_by);
        
        $this->get_query_fields();
        $this->query->set_where_group($this->options['date_method'], $this->options['date_group']);
        $this->granularity = $this->date_handler->arg_granularity($this->argument);
        $format = $this->date_handler->views_formats($this->granularity, 'sql');
    
        $this->placeholders = array();

        if (!empty($this->query_fields)) {
            // Use set_where_group() with the selected date_method
            // of 'AND' or 'OR' to create the where clause.
            foreach ($this->query_fields as $count => $query_field) {
                $field = $query_field['field'];
                $this->date_handler = $query_field['date_handler'];
                $this->field = $field['field_name'];
                $this->real_field = $field['field_name'];
                $this->table = $field['table_name'];
                $this->original_table = $field['table_name'];
                if ($field['table_name'] != $this->table || !empty($this->relationship)) {
                    $this->table = $this->query->ensure_table($field['table_name'], $this->relationship);
                }
                // $this->table_alias gets set when the first field is processed if otherwise empty.
                // For subsequent fields, we need to be sure it is emptied again.
                elseif (empty($this->relationship)) {
                    $this->table_alias = NULL;
                }
        
                $this->doQuery($group_by);

                $this->placeholders = array_merge($this->placeholders, $this->date_handler->placeholders);
            }
        }
    
    }
  
}
