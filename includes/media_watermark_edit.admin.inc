<?php

/**
 * @file
 * Media watermark module integration.
 * Main interface for CRUD actions.
 */

/**
 * Implements hook_form().
 */
function media_watermark_edit_settings($form, &$form_state) {
  $form = array();
  $output = media_watermark_render_table();
  $form['markup'] = array(
    '#type' => 'item',
    '#markup' => $output,
  );
  return $form;
}

/**
 * Function to create table of all watermarks.
 *
 * @return string
 *   An html of admin table.
 */
function media_watermark_render_table() {
  // Here we use theme_table.
  $header = array(
    'wid' => t('Edit/Delete Watermark'),
    'fid' => t('Image'),
    'name' => t('Name'),
    'hor_position' => t('Horizontal position'),
    'ver_position' => t('Vertical position'),
    'hor_margin' => t('Horizontal margin'),
    'ver_margin' => t('Vertical margin'),
    'alpha' => t('alpha'),
  );
  $rows = media_watermark_get_watermarks();
  // Here we will add edit delete links.
  foreach ($rows as $key => $value) {
    if (!empty($value['wid'])) {
      $wid = reset($value);
      $rows[$key]['wid'] = '<a style="padding-right:10px;" href="watermark/edit/' . $wid . '">' . t('Edit') . '</a><a href="watermark/delete/' . $wid . '">' . t('Delete') . '</a>';
      if (!empty($value['fid'])) {
        $file = file_load($value['fid']);
        $image = theme('image_formatter', array(
          'item' => array(
            'uri' => $file->uri,
            'alt' => t('edit'),
            'title' => t('Edit'),
          ),
          'path' => array(
            'path' => 'admin/config/media/watermark/edit/' . $wid,
            'options' => array('html' => TRUE),
          ),
          'image_style' => 'media_watermark',
        ));
        $rows[$key]['fid'] = $image;
      }
    }
  }
  $table_element = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('Your table is empty'),
  );
  return drupal_render($table_element);
}

