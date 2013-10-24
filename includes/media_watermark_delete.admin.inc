<?php

/**
 * @file
 * Media watermark module integration.
 *
 * Main interface for delete actions.
 */

/**
 * Menu callback: displays interface to delete watermark.
 *
 * Path: admin/config/media/watermark/delete/%.
 */
function media_watermark_delete_form($form, &$form_state) {
  $form_state['watermark_arg'] = arg(5);
  $name = media_watermark_get_name($form_state['watermark_arg']);
  if (!empty($name)) {
    $form['#submit'][] = 'media_watermark_form_submit';
    $question = t('Are you sure you want to delete %name?', array('%name' => $name));
    $path = 'admin/config/media/watermark';
    return confirm_form($form, $question, $path, NULL, t('Delete'), NULL, 'confirm');
  }
  else {
    print t('There is no watermark with this id, or it is misconfigured.');
  }
}

/**
 * Submit callback for media_watermark_delete_form() function.
 *
 * Delete watermark.
 *
 * @param array $form
 *   form array
 * @param array $form_state
 *   form state
 */
function media_watermark_form_submit($form, &$form_state) {
  db_delete('media_watermark')
    ->condition('wid', $form_state['watermark_arg'])
    ->execute();
  drupal_set_message(t('Watermark has been deleted.'));
  $form_state['redirect'] = 'admin/config/media/watermark';
}
