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
    '#upload_validators' => array('file_validate_extensions' => array('png')),
    '#description' => 'allowed files resolution is .png',
    '#required' => TRUE,
    '#default_value' => isset($values->fid) ? $values->fid : '',
  );
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => isset($values->name) ? $values->name : '',
    '#description' => t('Set watermark name, please.'),
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
  $form['alpha'] = array(
    '#type' => 'textfield',
    '#title' => t('Alpha level value'),
    '#default_value' => isset($values->alpha) ? $values->alpha : '90',
    '#required' => TRUE,
  );

  $form['#validate'][] = 'media_watermark_form_validate';
  $form['#submit'][] = 'media_watermark_form_submit';
  return system_settings_form($form);
}

/**
 * Validate watermark settings.
 */
function media_watermark_form_validate(&$form, &$form_state) {
}

/**
 * Submit callback for media_watermark_form() function.
 *
 * @param array $form
 * form array
 * @param array $form_state
 * from state array
 */
function media_watermark_form_submit($form, &$form_state) {
  if (isset($form_state['values']['watermark_image'])) {
    $data = array(
      'fid' => $form_state['values']['watermark_image'],
      'name' => $form_state['values']['name'],
      'hor_position' => $form_state['values']['hor_position'],
      'ver_position' => $form_state['values']['ver_position'],
      'hor_margin' => $form_state['values']['hor_margin'],
      'ver_margin' => $form_state['values']['ver_margin'],
      'alpha' => $form_state['values']['alpha'],
    );
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

    $file = file_load($form_state['values']['watermark_image']);
    $derivative_uri = image_style_path('media_watermark', $file->uri);
    // Create the image.
    $image_style = image_style_load('media_watermark');
    image_style_create_derivative($image_style, $file->uri, $derivative_uri);
    image_style_flush('media_watermark');

  }
  $form_state['redirect'] = 'admin/config/media/watermark';
}
