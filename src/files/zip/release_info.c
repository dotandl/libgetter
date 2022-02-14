/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021-2022 dotandl                          |
 * +----------------------------------------------------------+
 */

#include <getter/files/zip/release_info.h>
#include <getter/tools/error.h>
#include <stdio.h>
#include <stdlib.h>

GttReleaseInfo *gtt_zip_read_release_info(zip_t *zip, GttRelease *release) {
  char ri_json_path[GTT_BUFLEN];
  int status;
  zip_stat_t file_stat;
  zip_file_t *file;
  size_t bufsize;
  char *buf;
  GttReleaseInfo *ri;

  if (zip == NULL) {
    gtt_error(GTT_ZIP_ERROR, "Zip object is NULL");
    return NULL;
  }

  snprintf(ri_json_path, GTT_BUFLEN, "Releases/%s/%s/%s/GetterRelease.json",
           release->version, release->platform, release->arch);

  status = zip_stat(zip, ri_json_path, 0, &file_stat);
  if (status != 0) {
    gtt_error(GTT_ZIP_ERROR,
              "Error reading info about GetterRelease.json file");
    return NULL;
  }

  file = zip_fopen(zip, ri_json_path, 0);
  if (file == NULL) {
    gtt_error(GTT_ZIP_ERROR,
              "Error opening GetterRelease.json file within zip Box");
    return NULL;
  }

  bufsize = file_stat.size + 1;
  buf = calloc(bufsize, sizeof(char));

  status = zip_fread(file, buf, bufsize - 1);
  if (status < 0) {
    gtt_error(
        GTT_ZIP_ERROR,
        "Error reading contents of GetterRelease.json file withing zip Box");
    zip_fclose(file);
    free(buf);
    return NULL;
  }

  zip_fclose(file);

  ri = gtt_release_info_new_from_json(buf);
  if (GTT_FAILED) {
    /* Pass the error on */
    return NULL;
  }

  free(buf);

  gtt_ok();
  return ri;
}
