/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#define PCRE2_CODE_UNIT_WIDTH 8

#include <getter/release/version.h>
#include <getter/tools/error.h>
#include <getter/tools/version.h>
#include <getter/types/array.h>
#include <pcre2.h>
#include <stdbool.h>

GttRelease *gtt_get_latest_release_version(GttVector_release *releases) {
  GttVectorNode_release *node;
  GttRelease *latest;
  pcre2_code *regexp;
  pcre2_match_data *match_data;
  PCRE2_SIZE error_offset;
  int error_code, matches;

  PCRE2_UCHAR buf[8];
  PCRE2_SIZE buflen;

  int l_major, l_minor, l_patch,  // latest_...
      c_major, c_minor, c_patch;  // current_...

  regexp =
      pcre2_compile("([0-9]+)\\.([0-9]+)\\.([0-9]+)", PCRE2_ZERO_TERMINATED, 0,
                    &error_code, &error_offset, NULL);

  if (regexp == NULL) {
    gtt_error(GTT_REGEXP_COMPILATION_FAILED, "Could not compile regexp");
    return NULL;
  }

  l_major = 0;
  l_minor = 0;
  l_patch = 0;

  gtt_vector_for_each(releases, node) {
    match_data = pcre2_match_data_create_from_pattern(regexp, NULL);

    matches = pcre2_match(regexp, node->value->version,
                          strlen(node->value->version), 0, 0, match_data, NULL);

    buflen = arrlen(buf);
    pcre2_substring_copy_bynumber(match_data, 1, buf, &buflen);
    c_major = atoi(buf);

    buflen = arrlen(buf);
    pcre2_substring_copy_bynumber(match_data, 2, buf, &buflen);
    c_minor = atoi(buf);

    buflen = arrlen(buf);
    pcre2_substring_copy_bynumber(match_data, 3, buf, &buflen);
    c_patch = atoi(buf);

    if (gtt_is_newer(c_major, c_minor, c_patch, l_major, l_minor, l_patch)) {
      l_major = c_major;
      l_minor = c_minor;
      l_patch = c_patch;

      latest = node->value;
    }

    pcre2_match_data_free(match_data);
  }

  pcre2_code_free(regexp);

  gtt_ok();
  return latest;
}
