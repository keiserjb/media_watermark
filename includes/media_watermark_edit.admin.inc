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
  $output = media_watermark_get_sort_table_watermarks();
  $form['markup'] = array(
    '#type' => 'item',
    '#markup' => $output,
  );
  return $form;
}

/**
 * Function to get all watermarks array stored in db.
 *
 * @return string
 *   sorted table markup all watermarks with pagination
 */
function media_watermark_get_sort_table_watermarks() {
  $header = array(
    array('data' => t('Name'), 'field' => 'mw.name'),
    'fid' => t('Image'),
    array(
      'data' => t('Horizontal Position'),
      'field' => 'mw.hor_position'
    ),
    array(
      'data' => t('Vertical Position'),
      'field' => 'mw.ver_position'
    ),
    array(
      'data' => t('Horizontal Margin'),
      'field' => 'mw.hor_margin'
    ),
    array(
      'data' => t('Horizontal Margin'),
      'field' => 'mw.ver_margin'
    ),
    'edit' => t('Edit/Delete'),
  );

  $query = db_select('media_watermark', 'mw')
    ->fields('mw', array(
      'name',
      'fid',
      'hor_position',
      'ver_position',
      'hor_margin',
      'ver_margin',
      'wid',
    ));

  $query = $query->extend('TableSort')->orderByHeader($header);
  $query = $query->extend('PagerDefault')->limit(10);
  $rows = $query->execute();
  $rows = $rows->fetchAll(PDO::FETCH_ASSOC);
  if (!empty($rows)) {
    foreach ($rows as $key => $value) {
      if (!empty($value['fid'])) {
        $rows[$key]['name'] = $value['name'];
        $file = file_load($value['fid']);
        $image = theme('image_formatter', array(
          'item' => array(
            'uri' => $file->uri,
            'alt' => t('edit'),
            'title' => t('Edit'),
          ),
          'path' => array(
            'path' => 'admin/config/media/watermark/edit/' . $value['wid'],
            'options' => array('html' => TRUE),
          ),
          'image_style' => 'media_watermark',
        ));
        $rows[$key]['fid'] = $image;
        //Edit Delete.
        $edit_path = url('admin/config/media/watermark/edit/' . $value['wid']);
        $delete_path = url('admin/config/media/watermark/delete/' . $value['wid']);
        $rows[$key]['wid'] = '<a style="padding-right:10px;" href="' . $edit_path . '">' . t('Edit') . '</a><a href="' . $delete_path . '">' . t('Delete') . '</a>';
      }
    }
    //Prepare render array.
    $element['pager_table'] = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#empty' => t('Your table is empty'),
    );
    $element['pager_pager'] = array('#theme' => 'pager');
    return drupal_render($element);
  }
  else {
    return t('Please add at least one watermark.');
  }
}
