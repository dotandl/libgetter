/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/files/zip/box_info.h>
#include <getter/tools/error.h>
#include <stdlib.h>
#include <zip.h>

GttBoxInfo *gtt_zip_read_box_info(const char *filename) {
  GttBoxInfo *bi;
  int status;
  zip_t *zip;
  zip_stat_t file_stat;
  zip_file_t *file;
  size_t bufsize;
  char *buf;

  zip = zip_open(filename, ZIP_RDONLY, NULL);

  if (zip == NULL) {
    gtt_error(GTT_ZIP_ERROR, "Error opening zip file");
    return NULL;
  }

  status = zip_stat(zip, "GetterBox.json", 0, &file_stat);

  if (status != 0) {
    gtt_error(GTT_ZIP_ERROR,
              "Error reading info about GetterBox.json file within Box file");
    zip_close(zip);
    return NULL;
  }

  file = zip_fopen(zip, "GetterBox.json", 0);

  if (file == NULL) {
    gtt_error(GTT_ZIP_ERROR,
              "Error opening GetterBox.json file within Box file");
    zip_close(zip);
    return NULL;
  }

  bufsize = file_stat.size + 1;
  buf = calloc(bufsize, sizeof(char));

  status = zip_fread(file, buf, bufsize - 1);

  if (status < 0) {
    gtt_error(GTT_ZIP_ERROR,
              "Error reading contents of GetterBox.json file within Box file");
    zip_fclose(file);
    zip_close(zip);
    free(buf);
    return NULL;
  }

  bi = gtt_box_info_new_from_json(buf);

  if (GTT_FAILED) {
    // pass the error on
    free(buf);
    zip_fclose(file);
    zip_close(zip);
    return NULL;
  }

  free(buf);
  zip_fclose(file);
  zip_close(zip);

  gtt_ok();
  return bi;
}
