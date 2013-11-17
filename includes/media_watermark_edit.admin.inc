<?php

/**
 * @file
 * Media watermark module integration.
 *
 * Main interface for CRUD actions.
 */

/**
 * Form constructor for the media watermark edit settings form.
 *
 * @ingroup forms
 */
function media_watermark_edit_settings($form, &$form_state) {
  $form = array();
  $output = media_watermark_get_sort_table_watermarks();
  $form['markup'] = array(
    '#type' => 'item',
    '#markup' => $output,
  );

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'media_watermark') . '/media_watermark.css',
  );

  return $form;
}

/**
 * Function to get all watermarks array stored in db.
 *
 * Also display them as sortable table with pagination.
 *
 * @return string
 *   sorted table markup all watermarks with pagination
 */
function media_watermark_get_sort_table_watermarks() {
  $header = array(
    array(
      'data' => t('Image'),
      'field' => 'mw.fid',
    ),
    array(
      'data' => t('Name'),
      'field' => 'mw.name',
    ),
    array(
      'data' => t('Horizontal Position'),
      'field' => 'mw.hor_position',
    ),
    array(
      'data' => t('Vertical Position'),
      'field' => 'mw.ver_position',
    ),
    array(
      'data' => t('Horizontal Margin'),
      'field' => 'mw.hor_margin',
    ),
    array(
      'data' => t('Horizontal Margin'),
      'field' => 'mw.ver_margin',
    ),
    array(
      'data' => t('Edit/Delete'),
      'field' => 'mw.wid',
    ),
  );

  $query = db_select('media_watermark', 'mw')
    ->fields('mw', array(
      'fid',
      'name',
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
        $rows[$key]['name'] = $value['name'];
        // Edit Delete.
        $edit_path = l(t('Edit'), 'admin/config/media/watermark/edit/' . $value['wid'], array('attributes' => array('class' => array('padding-right'))));
        $delete_path = l(t('Delete'), 'admin/config/media/watermark/delete/' . $value['wid']);
        // Used render to add two links using l() function in one array element.
        $rows[$key]['wid'] = render($edit_path);
        $rows[$key]['wid'] .= render($delete_path);
      }
    }
    // Prepare render array.
    $element['pager_table'] = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#empty' => t('Your table is empty'),
    );
    $element['pager_pager'] = array('#theme' => 'pager');
    // Need to render elements to put them into form as #markup.
    return drupal_render($element);
  }
  else {
    return t('Please add at least one watermark.');
  }
}
