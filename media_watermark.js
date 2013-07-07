(function ($) {

    Drupal.behaviors.media_watermark = {
        attach: function (context, settings) {
            jQuery('#edit-watermarks-images .image-hidden').hide();
            jQuery('#edit-watermarks-images .image-hidden').first().show();
            jQuery("#edit-no-watermark").click(function(){
                if($('input[name=no_watermark]').is(':checked')){
                    jQuery('.form-item-watermarks-names').hide();
                    jQuery('#edit-watermarks-images .image-hidden').hide();
                } else {
                    jQuery('.form-item-watermarks-names').show();
                    jQuery('#edit-watermarks-images .image-hidden').first().show();
                    jQuery('#edit-watermarks-names option').first().attr('selected', true);
                    jQuery('#edit-watermarks-names').siblings('span.custom-select')
                        .find('span span')
                        .text(jQuery('#edit-watermarks-names option').first().text());

                }
            });
            jQuery('#edit-watermarks-names').change(function(){
                var val = jQuery(this+':selected').val();
                jQuery('#edit-watermarks-images .image-hidden').hide();
                jQuery('#edit-watermarks-images #image-' + val).show();
            });
        }
    };
})(jQuery);