/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021-2022 dotandl                          |
 * +----------------------------------------------------------+
 */

#include <getter/files/zip/box.h>
#include <getter/files/zip/package.h>
#include <getter/files/zip/release_extract.h>
#include <getter/files/zip/release_info.h>
#include <getter/release/extracted_release.h>
#include <getter/tools/error.h>

void gtt_zip_package_install(zip_t *zip) {
  GttBox *box;
  GttRelease *release;
  GttReleaseInfo *ri;
  GttExtractedRelease *er;
  char tmp_release_path[GTT_BUFLEN];

  if (zip == NULL) {
    gtt_error(GTT_ZIP_ERROR, "Zip object is NULL");
    return;
  }

  box = gtt_zip_read_box(zip);
  if (GTT_FAILED) {
    /* pass the error on */
    return;
  }

  release = gtt_box_get_appropriate_release(box);
  if (GTT_FAILED) {
    gtt_box_delete(box);
    /* pass the error on */
    return;
  }

  ri = gtt_zip_read_release_info(zip, release);
  if (GTT_FAILED) {
    gtt_box_delete(box);
    /* pass the error on */
    return;
  }

  er = gtt_extracted_release_new(release, ri, box->info);
  if (GTT_FAILED) {
    gtt_box_delete(box);
    gtt_release_info_delete(ri);
    /* pass the error on */
    return;
  }

  gtt_zip_extract_release(zip, release, tmp_release_path, GTT_BUFLEN);
  if (GTT_FAILED) {
    gtt_box_delete(box);
    gtt_release_info_delete(ri);
    gtt_extracted_release_delete(er);
    /* pass the error on */
    return;
  }

  gtt_box_delete(box);
  gtt_release_info_delete(ri);
  gtt_extracted_release_delete(er);

  gtt_ok();
}
