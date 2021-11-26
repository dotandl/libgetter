/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/tools/error.h>
#include <getter/types/array.h>
#include <stdio.h>

GttError gtt_last_error = {0};

void gtt_error(GttErrorCode err_code, const char *err_desc) {
  gtt_last_error.code = err_code;

  if (err_desc != NULL) {
    snprintf(gtt_last_error.desc, GTT_BUFLEN, "%s", err_desc);
  } else {
    *gtt_last_error.desc = 0;  // clear the string
  }
}
