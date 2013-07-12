<?php

/**
 * @file
 * Media watermark module integration.
 * Main interface for delete actions.
 */

/**
 * Implements hook_form().
 * @param $form
 * @param $form_state
 * @return mixed
 */
function media_watermark_delete_form($form, &$form_state) {
  $name = media_watermark_get_name(arg(5));
  if (!empty($name)) {
    $form['delete_watermark'] = array(
      '#type' => 'item',
      '#markup' => t('Are you sure you want to delete?') . $name,
      '#default_value' => '90',
      '#required' => TRUE,
    );

    $form['#submit'][] = 'media_watermark_form_submit';
    return system_settings_form($form);
  }
  else {
    print t('There is no watermark with this id, or it is misconfigured.');
  }
}

/**
 * Submit callback for media_watermark_delete_form() function.
 * Submit watermark settings.
 * @param $form
 * @param $form_state
 */
function media_watermark_form_submit($form, &$form_state) {
  db_delete('media_watermark')
    ->condition('wid', arg(5))
    ->execute();
  drupal_set_message(t('Watermark has been deleted.'));
  $form_state['redirect'] = 'admin/config/media/watermark';
}