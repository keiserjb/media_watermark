/**
 * @file
 * Media watermark module javascript file.
 * 
 * Contains javascript for admin interface of media watermark module.
 */

(function ($) {

    Drupal.behaviors.flex2_media_watermark = {
        attach: function (context, settings) {
            $('.hide-select-list').hide();
            $('#edit-watermarks-images .image-hidden').hide();
            $('.form-item-watermarks-names').hide();
            $("#edit-add-watermark").click(function(){
                if($('input[name=add_watermark]').is(':checked')){
                    $('#edit-upload-upload-button, #edit-upload-remove-button').hide();
                    $('#edit-watermarks-images .image-hidden').first().show();
                    $('.form-item-watermarks-names').show();
                    $('#edit-watermarks-names option').first().attr('selected', true);
                    $('#edit-watermarks-names').siblings('span.custom-select')
                        .find('span span')
                        .text($('#edit-watermarks-names option').first().text());
                } else {
                    $('#edit-upload-upload-button, #edit-upload-remove-button').show();
                    $('.form-item-watermarks-names').hide();
                    $('#edit-watermarks-images .image-hidden').hide();
                }
            });
            $('#edit-watermarks-names').change(function(){
                var val = $('#edit-watermarks-names :selected').val();
                $('#edit-watermarks-images .image-hidden').hide();
                $('#edit-watermarks-images #image-' + val).show();
            });
        }
    };
})(jQuery);
