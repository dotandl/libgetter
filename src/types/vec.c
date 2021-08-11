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

void vec_keyval_free(vec_keyval_t *vec) {
  GttKeyVal kv;
  int i;

  if (vec == NULL) return;

  vec_foreach(vec, kv, i) {
    if (kv.key != NULL) free(kv.key);
    if (kv.val != NULL) free(kv.val);
  }

  free(vec);
}
