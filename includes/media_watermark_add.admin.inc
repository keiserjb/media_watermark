<?php
/**
 * @file
 * Media watermark module integration.
 * Main interface for insert and update actions.
 */

/**
 * Implements hook_form().
 */
function media_watermark_form($form, &$form_state) {
  if (arg(5)) {
    drupal_set_title(t('Edit watermark'));
    $values = media_watermark_get_watermark(arg(5));
  }
  $form['#attributes'] = array('enctype' => "multipart/form-data");
  $form['watermark_image'] = array(
    '#type' => 'managed_file',
    '#title' => t('Watermark image'),
    '#upload_location' => 'public://watermark',
    '#upload_validators' => array('file_validate_extensions' => array('png gif')),
    '#description' => 'allowed files extensions are .png and .gif',
    '#required' => TRUE,
    '#default_value' => isset($values->fid) ? $values->fid : '',
  );
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => isset($values->name) ? $values->name : '',
    '#description' => t('Set watermark name.'),
    '#required' => TRUE,
  );
  $form['hor_position'] = array(
    '#type' => 'select',
    '#title' => t('Horizontal position of watermark'),
    '#options' => array(
      'left' => t('left'),
      'middle' => t('middle'),
      'right' => t('right'),
    ),
    '#default_value' => isset($values->hor_position) ? $values->hor_position : 'left',
    '#required' => TRUE,
  );
  $form['ver_position'] = array(
    '#type' => 'select',
    '#title' => t('Vertical position of watermark'),
    '#options' => array(
      'top' => t('top'),
      'center' => t('center'),
      'bottom' => t('bottom'),
    ),
    '#default_value' => isset($values->ver_position) ? $values->ver_position : 'bottom',
    '#required' => TRUE,
  );
  $form['hor_margin'] = array(
    '#type' => 'textfield',
    '#title' => t('Horizontal margin, px'),
    '#default_value' => isset($values->hor_margin) ? $values->hor_margin : '0',
    '#description' => t('Set minus or plus signed value for moving watermark to left or right from defined position.'),
    '#required' => TRUE,
  );
  $form['ver_margin'] = array(
    '#type' => 'textfield',
    '#title' => t('Vertical margin, px'),
    '#default_value' => isset($values->ver_margin) ? $values->ver_margin : '0',
    '#description' => t('Set minus or plus signed value for moving watermark to higher or lower from defined position.'),
    '#required' => TRUE,
  );

  //We add or update watermarks in validation function.
  //Against this issue https://drupal.org/node/979158.
  $form['#validate'][] = 'media_watermark_form_validate';
  return system_settings_form($form);
}

/**
 * Validate callback for media_watermark_form() function.
 *
 * @param array $form
 *   form array
 * @param array $form_state
 *   from state array
 */
function media_watermark_form_validate(&$form, &$form_state) {
  if (isset($form_state['values']['watermark_image'])) {
    $data = array(
      'fid' => $form_state['values']['watermark_image'],
      'name' => $form_state['values']['name'],
      'hor_position' => $form_state['values']['hor_position'],
      'ver_position' => $form_state['values']['ver_position'],
      'hor_margin' => $form_state['values']['hor_margin'],
      'ver_margin' => $form_state['values']['ver_margin'],
    );
    $file = file_load($form_state['values']['watermark_image']);
    $file->status = FILE_STATUS_PERMANENT;
    file_save($file);
    global $user;
    file_usage_add($file, 'media_watermark', 'image', $user->uid);

    if (arg(5)) {
      db_update('media_watermark')
        ->fields($data)
        ->condition('wid', arg(5))
        ->execute();
      drupal_set_message(t("Watermark has been updated."));

    }
    else {
      db_insert('media_watermark')
        ->fields($data)
        ->execute();
      drupal_set_message(t("Watermark has been added."));
    }
  }
  $form_state['redirect'] = 'admin/config/media/watermark';
}

