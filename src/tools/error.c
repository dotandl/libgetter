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
#include <string.h>

GttError gtt_last_error = {0};

void gtt_error(GttErrorCode err_code, const char *err_desc) {
  gtt_last_error.code = err_code;

  if (err_desc != NULL) {
    strncpy(gtt_last_error.desc, err_desc, arrlen(gtt_last_error.desc) - 1);
  } else {
    *gtt_last_error.desc = 0;  // clear the string
  }
}
