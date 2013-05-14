<?php
/**
 * @file
 * WebTree Installation Profile
 */

/**
 * Implements hook_form_FORM_ID_alter()
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
