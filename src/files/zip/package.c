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
#include <getter/script/script_runner.h>
#include <getter/tools/error.h>
#include <getter/tools/tmp.h>

void gtt_zip_package_install(zip_t *zip) {
  GttBox *box;
  GttRelease *release;
  GttReleaseInfo *ri;
  GttExtractedRelease *er;
  GttScriptRunner *sr;
  char script_path[GTT_BUFLEN];
  char tmp_release_path[GTT_BUFLEN];
  int (*funcs[4])(const char *, const char *);
  size_t i;
  int status;

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

  snprintf(script_path, GTT_BUFLEN, "%s/%s", tmp_release_path, er->script);

  sr = gtt_script_runner_get(script_path);
  if (sr == NULL) {
    gtt_rmtmpdir(tmp_release_path);
    gtt_box_delete(box);
    gtt_release_info_delete(ri);
    gtt_extracted_release_delete(er);

    gtt_error(GTT_INCOMPATIBLE_SCRIPT_ERROR,
              "Could not find an appropriate script runner");
    return;
  }

  funcs[0] = sr->prepare;
  funcs[1] = sr->build;
  funcs[2] = sr->install;
  funcs[3] = sr->clean;

  for (i = 0; i < sizeof(funcs) / sizeof(*funcs); i++) {
    status = funcs[i](script_path, tmp_release_path);
    if (status != 0) {
      gtt_rmtmpdir(tmp_release_path);
      gtt_box_delete(box);
      gtt_release_info_delete(ri);
      gtt_extracted_release_delete(er);

      gtt_error(GTT_SCRIPT_ERROR, "GetterScript exited with non-0 exit code");
      return;
    }
  }

  gtt_box_delete(box);
  gtt_release_info_delete(ri);
  gtt_extracted_release_delete(er);

  gtt_ok();
}
