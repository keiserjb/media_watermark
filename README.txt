CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Installation



INTRODUCTION
------------

Current Maintainer: Bogdan Tur <bogdan.tur1988@gmail.com>

Media Watermark module give possibility to add watermark image to files uploaded
through media module. This module support batch operations while we upload
multiple images with watermarking using plupload widget. If we don't need to add
watermark while upload we just need to check "No watermark" checkbox. I should
notice that watermark could be added only to .jpg, .jpeg image files, and
watermarking file should be .png.


INSTALLATION
------------

1. This module REQUIRES media module.

2. Copy this media_watermark/ directory to sites/SITENAME/modules directory.

3. Enable the module and configure admin/config/media/watermark.

4. Add watermarks using path admin/config/media/watermark/add

5. Then you will find watermarks on media files uploading forms admin/content/media -> + Add file.
