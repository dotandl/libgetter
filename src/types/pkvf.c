/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/types/pkvf.h>
#include <stdio.h>
#include <string.h>

bool gtt_parse_pkvf(const char *pkvf, vec_keyval_t *vec) {
  size_t key_len, val_len;
  char *line_ptr, *seq_ptr, *key, *val;
  GttKeyVal kv;

  vec_init(vec);

  line_ptr = strtok((char *)pkvf, "\n");
  while (line_ptr != NULL) {
    if (strcmp(line_ptr, "") == 0) goto skip;

    if ((seq_ptr = strstr(line_ptr, "@#@")) == NULL) return false;

    key_len = seq_ptr - line_ptr;
    val_len = strlen(seq_ptr + 3);

    key = calloc(key_len + 1, sizeof(char));
    val = calloc(val_len + 1, sizeof(char));

    // key starts at the start of the line
    sprintf(key, "%.*s", key_len, line_ptr);
    // val starts 3 characters after the sequence
    sprintf(val, "%.*s", val_len, seq_ptr + 3);

    kv = (GttKeyVal){key, val};
    vec_push(vec, kv);

  skip:
    line_ptr = strtok(NULL, "\n");
  }

  return true;
}
