<?php
/**
 * flex2_media_watermark settings form.
 */
function flex2_media_watermark_edit_settings($form, &$form_state) {
  $form = array();
  $output = flex2_media_watermark_render_table();
  $form['markup'] = array(
    '#type' => 'item',
    '#markup' => $output,
  );
  return $form;
}

/**
 * function to create table of all watermarks
 */
function flex2_media_watermark_render_table() {
  //here we use theme_table
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
  $rows = flex2_media_watermark_get_watermarks();
  //here we will add edit delete links
  foreach ($rows as $key => $value) {
    $wid = reset($value);
    $rows[$key]['wid'] = '<a style="padding-right:10px;" href="watermark/edit/' . $wid . '">' . t('Edit') . '</a><a href="watermark/delete/' . $wid . '">' . t('Delete') . '</a>';
    foreach ($value as $key1 => $value1) {
      if ($key1 == 'fid') {
        $file = file_load($value1);
        $image = theme('image_formatter', array(
          'item' => array(
            'uri' => $file->uri,
            'alt' => t('edit'),
            'title' => t('Edit')
          ),
          'path' => array(
            'path' => 'admin/config/media/watermark/edit/' . $wid,
            'options' => array('html' => TRUE,),
          ),
          'image_style' => 'watermark_330x120',
        ));
      }
      $rows[$key]['fid'] = $image;
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
