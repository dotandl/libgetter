/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#define PCRE2_CODE_UNIT_WIDTH 8

#include <getter/files/zip/box.h>
#include <getter/files/zip/box_info.h>
#include <getter/tools/error.h>
#include <getter/types/array.h>
#include <pcre2.h>
#include <string.h>
#include <zip.h>

GttBox *gtt_zip_read_box(zip_t *zip) {
  /* common */
  int status, i, j;

  /* libgetter */
  GttBoxInfo *bi;
  GttPtrArr releases;

  /* libzip */
  int entries;
  char *entry_name;

  /* pcre2 */
  pcre2_code *regexp;
  pcre2_match_data *match_data;
  PCRE2_SIZE error_offset, buflen;
  PCRE2_UCHAR version_buf[GTT_BUFLEN], platform_buf[GTT_BUFLEN],
      arch_buf[GTT_BUFLEN];
  int matches;

  if (zip == NULL) {
    gtt_error(GTT_ZIP_ERROR, "Zip object is NULL");
    return NULL;
  }

  regexp =
      pcre2_compile("(?i)^Releases\\/([^\\/]+)\\/([^\\/]+)\\/([^\\/]+)\\/$",
                    PCRE2_ZERO_TERMINATED, 0, &status, &error_offset, NULL);

  if (regexp == NULL) {
    gtt_error(GTT_REGEXP_COMPILATION_FAILED, "Could not compile regexp");
    return NULL;
  }

  entries = zip_get_num_entries(zip, 0);

  j = 0;
  releases = gtt_ptr_arr_new(0);

  for (i = 0; i < entries; i++) {
    entry_name = (char *)zip_get_name(zip, i, 0);

    if (entry_name == NULL) {
      pcre2_code_free(regexp);
      gtt_error(GTT_ZIP_ERROR, "Error resolving the name of zip file's entry");
      return NULL;
    }

    match_data = pcre2_match_data_create_from_pattern(regexp, NULL);
    matches = pcre2_match(regexp, entry_name, strlen(entry_name), 0, 0,
                          match_data, NULL);

    /* we have match */
    if (matches > 0) {
      buflen = GTT_BUFLEN;
      pcre2_substring_copy_bynumber(match_data, 1, version_buf, &buflen);

      buflen = GTT_BUFLEN;
      pcre2_substring_copy_bynumber(match_data, 2, platform_buf, &buflen);

      buflen = GTT_BUFLEN;
      pcre2_substring_copy_bynumber(match_data, 3, arch_buf, &buflen);

      gtt_ptr_arr_resize(&releases, -1);
      releases.arr[j++] = gtt_release_new(platform_buf, arch_buf, version_buf);
    }

    pcre2_match_data_free(match_data);
  }

  pcre2_code_free(regexp);

  bi = gtt_zip_read_box_info(zip);
  if (GTT_FAILED) return NULL; /* pass the error on */

  gtt_ok();
  return gtt_box_new(bi, releases);
}
