<?php
/**
 * @file
 * FOCUS Distribution Profile.
 */

module_load_include('inc', 'focus', 'includes/debug');
module_load_include('inc', 'focus', 'includes/libraries');
module_load_include('inc', 'focus', 'includes/preprocess');

/**
 * Implements hook_views_api()
 */
function focus_views_api() {
    return array(
        'api' => 3,
    );
}

/**
 * Implements hook_custom_theme().
 */
function focus_custom_theme() {
    switch ($_GET['q']) {
        case 'user':
            return variable_get('admin_theme', variable_get('theme_default'));
    }
}

/**
 * Implements hook_admin_paths().
 */
function focus_admin_paths() {
    if (variable_get('node_admin_theme')) {
        $paths = array(
            'user'   => TRUE,
            'user/*' => TRUE,
        );
        return $paths;
    }
}

/**
 * Implements hook_filter_info().
 */
function focus_filter_info() {
    
    $filters['focus_caption'] = array(
        'title' => t('FOCUS Image Caption'),
        'description' => t("Adds captions to images"),
        'process callback' => 'focus_filter_caption',
        'weight' => 10,
        'cache' => FALSE,
    );
    
    return $filters;
    
}

/**
 * Callback for hook_filter_info.
 */
function focus_filter_caption($text) {
    return preg_replace_callback("#\<img.*?\>#i", 'focus_filter_caption_callback', $text);
}

/**
 * Callback for preg_replace_callback.
 */
function focus_filter_caption_callback($match) {
    $image = reset($match);
    
    if (!is_string($image)) throw new Exception('Unable to find matching tag');
    
    preg_match_all('#title="(.*?)"#i', $image, $title);
    
    $output = '<span class="inline-image-wrapper">';
    $output .= '<span class="inline-image">';
    $output .= $image;
    
    if (!empty($title[1][0])) {
        $output .= "<span class='inline-image-caption'>{$title[1][0]}</span>";
    }
    
    $output .= '</span></span>';
    
    return $output;
}

/**
 * Implements hook_form_FORM_ID_alter().
 * 
 * We use 'system' for the hook because this form is before the full Drupal Bootstrap
 * @see http://drupal.org/node/1153646
 */
function system_form_install_settings_form_alter(&$form, $form_state) {

    if (!empty($form['settings']['mysql'])) {
        $form['settings']['mysql']['database']['#description'] = 
            str_replace(' It must exist on your server before FOCUS can be installed.', '', $form['settings']['mysql']['database']['#description']);
        
        $form['settings']['mysql']['database_new'] = array(
            '#type' => 'checkbox',
            '#title' => st('Create New Database'),
            '#default_value' => FALSE,
            '#description' => st('If the database does not yet exist on this server, one will be created for you.'),
            '#states' => array(
                'visible' => array(
                    ':input[name="driver"]' => array('value' => 'mysql'),
                ),
            ),
            '#weight' => 0.0001,
        );
        
        // put custom validation ahead of the existing validation
        array_unshift($form['#validate'], 'focus_install_settings_form_validate');
        
        // put custom submit ahead of the existing submit
        array_unshift($form['actions']['save']['#submit'], 'focus_install_settings_form_submit');
    }

}

/**
 * Form validation callback
 * 
 * Creates new database if we can connect with the provided credentials and the option was chosen
 */
function focus_install_settings_form_validate(&$form, &$form_state) {

    if (empty($form_state['values']['mysql']['database_new'])) return;
    
    $mysql = $form_state['values']['mysql'];
    
    $database = (empty($mysql['prefix']))
        ? $mysql['database']
        : $mysql['prefix'].'_'.$mysql['database'];
    
    if ($connect = mysql_connect($mysql['host'], $mysql['username'], $mysql['password'])) {
        mysql_query("CREATE DATABASE IF NOT EXISTS `$database`");
    }

}
 
/**
 * Form submit callback
 * 
 * Removes the database_new key to prevent it from appearing in settings.php
 */
function focus_install_settings_form_submit(&$form, &$form_state) {

    if (isset($form_state['values']['mysql']['database_new'])) {
        unset($form_state['values']['mysql']['database_new']);
    }

    if (isset($form_state['storage']['database']['database_new'])) {
        unset($form_state['storage']['database']['database_new']);
    }

}

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function focus_form_install_configure_form_alter(&$form, $form_state) {

    // set default country so we don't have to constantly select it
    $form['server_settings']['site_default_country']['#default_value'] = 'US';
    
    // by default, we don't want updates
    $form['update_notifications']['update_status_module']['#default_value'] = array(0, 0);
    
    // expose the clean_url option
    $form['clean_url']['#type'] = 'checkbox';
    $form['clean_url']['#title'] = st('Enable clean urls?');
    $form['clean_url']['#default_value'] = 1;
    
    // add custom validator
    $form['#validate'][] = 'focus_install_configure_form_validate';
    
    // add custom submit
    $form['#submit'][] = 'focus_install_configure_form_submit';
    
    // optional dandelion script builder
    $form['dandelion_create'] = array(
        '#type' => 'checkbox',
        '#title' => t('Create Dandelion File?'),
        '#description' => t('Dandelion is a ruby gem that can manage your site deployment easily.  !more.', array('!more' => l(t('More Information'), 'http://rubygems.org/gems/dandelion', array('attributes' => array('target' => '_blank'))))),
        '#default_value' => FALSE,
        '#weight' => -50,
    );
    
    $form['dandelion'] = array(
        '#type' => 'fieldset',
        '#title' => t('FTP Information'),
        '#tree' => TRUE,
        '#weight' => -49,
        '#states' => array(
            'visible' => array(
                'input[name="dandelion_create"]' => array('checked' => TRUE),
            ),
        ),
    );
    
    $form['dandelion']['scheme'] = array(
        '#type' => 'select',
        '#title' => t('Scheme'),
        '#options' => array(
            'ftp' => t('FTP'),
            'sftp' => t('SFTP'),
        ),
        '#default_value' => 'sftp',
    );
    
    $form['dandelion']['host'] = array(
        '#type' => 'textfield',
        '#title' => t('Host'),
    );
    
    $form['dandelion']['username'] = array(
        '#type' => 'textfield',
        '#title' => t('Username'),
    );
    
    $form['dandelion']['password'] = array(
        '#type' => 'textfield',
        '#title' => t('Password'),
    );
    
    $form['dandelion']['path'] = array(
        '#type' => 'textfield',
        '#title' => t('Path'),
    );
    
    $exclude = array(
        '.gitignore',
        '.htaccess',
        'dandelion.yml',
        'Makefile',
    );
    
    $form['dandelion']['exclude'] = array(
        '#type' => 'textarea',
        '#title' => t('Files to Exclude'),
        '#description' => t('Put one file per line. Use a path relative to your Drupal root.'),
        '#default_value' => implode("\r\n", $exclude),
    );

}

/**
 * Form validation callback
 */
function focus_install_configure_form_validate($form, &$form_state) {

    // for security, we should never allow an account with the name of 'admin'
    if (isset($form_state['values']['account']['name']) && $form_state['values']['account']['name'] == 'admin') {
        form_set_error('account][name', t('For security, username cannot be: '.$form_state['values']['account']['name']));
    }

}

/**
 * Form submit callback
 */
function focus_install_configure_form_submit($form, &$form_state) {

    if (empty($form_state['values']['dandelion_create'])) return;

    $values = $form_state['values']['dandelion'];
    $file = DRUPAL_ROOT . '/dandelion.yml';
    focus_install_dandelion_write($file, $values);

}

/**
 * Write to dandelion file
 */
function focus_install_dandelion_write($file, $values) {

    $data = '';

    foreach ($values as $key => $value) {
        if ($key == 'exclude') {
            $exclude = explode("\r\n", $value);
            $data .= "$key:\r\n";
            foreach ($exclude as $exfile) {
                $data .= "  - $exfile\r\n";
            }
        } else {
            $data .= "$key: $value\r\n";
        }
    }

    file_put_contents($file, utf8_encode($data));

}

/**
 * Implements hook_theme_registry_alter()
 */
function focus_theme_registry_alter(&$theme_registry) {
    $theme_registry['colorbox_image_formatter']['preprocess functions'][] = 'focus_colorbox_image_formatter_preprocess';
}

/**
 * Theme preprocessor
 * Adds fielded values to file itself
 */
function focus_colorbox_image_formatter_preprocess(&$vars) {

    // set alt to fielded alt
    if (!empty($vars['item']['field_file_image_alt_text'][LANGUAGE_NONE][0]['value'])) {
        $vars['item']['alt'] = $vars['item']['field_file_image_alt_text'][LANGUAGE_NONE][0]['value'];
    }

    // set title to fielded title
    if (!empty($vars['item']['field_file_image_title_text'][LANGUAGE_NONE][0]['value'])) {
        $vars['item']['title'] = $vars['item']['field_file_image_title_text'][LANGUAGE_NONE][0]['value'];
    }

}

/**
 * Implements hook_preprocess_html().
 */
function focus_preprocess_html(&$vars) {
    // if we're using JIRA Issue Collector, override the styles.
    // TODO: don't explicitly set the css here.  Instead point it to the active
    // theme to allow it to override these styles.
    // if (module_exists('jira_issue_collector')) {
        // drupal_add_css(FOCUS_CORE_PATH . '/css/jira.css', array('group' => CSS_THEME, 'weight' => 20));
    // }
}

/**
 * Implements hook_wysiwyg_editor_settings_alter().
 * 
 * @see http://drupal.org/node/1951964
 */
function focus_wysiwyg_editor_settings_alter(&$settings, $context) {
    if ($context['profile']->editor == 'ckeditor') {
        $settings['allowedContent'] = TRUE;
    }
}

/**
 * Implements hook_page_build().
 */
function focus_page_build(&$page) {
    $page['page_top']['focus_legacy'] = array(
        '#type' => 'container',
        '#attributes' => array('class' => 'chromeframe'),
        '#weight' => -1000,
        '#prefix' => t('<!--[if lte IE 7]>'),
        '#suffix' => t('<![endif]-->'),
        'content' => array(
            '#type' => 'html_tag',
            '#tag' => 'p',
            '#value' => t('You are using an <em>outdated</em> browser.  Please !upgrade or !chromeframe to improve your experience.', array(
                '!upgrade' => l('upgrade your browser', 'http://browsehappy.com', array(
                    'attributes' => array(
                        'target' => '_blank',
                    ),
                )),
                '!chromeframe' => l('activate Google Chrome Frame', 'http://www.google.com/chromeframe/', array(
                    'query' => array('redirect' => 'true'),
                )),
            )),
        ),
    );
}
