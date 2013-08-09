CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Installation



INTRODUCTION
------------

Current Maintainer: Bogdan Tur <bogdan.tur1988@gmail.com>

Media Watermark module give possibility to add watermark image to files uploaded
through media module. This module support batch operations while we upload
multiple images with watermarking.


INSTALLATION
------------

The bot.module is not like other Drupal modules and requires a bit more
effort than normal to get going. Unlike a regular Drupal page load, an
IRC bot has to run forever and, for reasons best explained elsewhere, this
entails running the bot through a shell NOT through web browser access.

1. This module REQUIRES media module.

2. Copy this media_watermark/ directory to sites/SITENAME/modules directory.

3. Enable the module and configure admin/config/media/watermark.

4. Add watermarks using path admin/config/media/watermark/add

5. Then you will find watermarks on media files uploading forms.