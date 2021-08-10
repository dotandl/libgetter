/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/types/vec.h>

void vec_str_free(vec_str_t *vec) {
  char *str;
  int i;

  if (vec == NULL) return;

  vec_foreach(vec, str, i) {
    if (str != NULL) free(str);
  }

  free(vec);
}
