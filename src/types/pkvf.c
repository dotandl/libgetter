/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#define CVECTOR_LOGARITHMIC_GROWTH

#include <cvector.h>
#include <getter/tools/error.h>
#include <getter/types/pkvf.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#define strtok_r strtok_s
#endif

static cvector_vector_type(char *) pkvf_value_to_vec(const char *val);

cvector_vector_type(GttPKVFToken) gtt_parse_pkvf(const char *pkvf) {
  size_t key_len, val_len;
  char *line_ptr, *save_ptr, *seq_ptr, *key, *val;
  cvector_vector_type(GttPKVFToken) vec;
  cvector_vector_type(char *) vals;
  GttPKVFToken token;
  GttPKVFTokenValue token_value;

  vec = NULL;

  line_ptr = strtok_r((char *)pkvf, "\n", &save_ptr);
  while (line_ptr != NULL) {
    if (strcmp(line_ptr, "") == 0) goto skip;

    if ((seq_ptr = strstr(line_ptr, "@#@")) == NULL) {
      gtt_vector_pkvf_token_free(vec);

      gtt_error(GTT_PARSE_ERROR, "Could not parse PKVF string");
      return NULL;
    }

    key_len = seq_ptr - line_ptr;
    val_len = strlen(seq_ptr + 3);

    key = calloc(key_len + 1, sizeof(char));
    val = calloc(val_len + 1, sizeof(char));

    // key starts at the start of the line
    sprintf(key, "%.*s", key_len, line_ptr);
    // val starts 3 characters after the sequence
    sprintf(val, "%.*s", val_len, seq_ptr + 3);

    if (strstr(val, "@,@")) {
      vals = pkvf_value_to_vec(val);
      free(val);

      token_value.vec = vals;
      token.type = GTT_PKVF_STRING_VECTOR_TOKEN;
    } else {
      token_value.str = val;
      token.type = GTT_PKVF_STRING_TOKEN;
    }

    token.key = key;
    token.val = token_value;

    cvector_push_back(vec, token);

  skip:
    line_ptr = strtok_r(NULL, "\n", &save_ptr);
  }

  gtt_ok();
  return vec;
}

void gtt_vector_pkvf_token_free(cvector_vector_type(GttPKVFToken) vec) {
  int i, j;

  if (vec == NULL) return;

  for (i = 0; i < cvector_size(vec); i++) {
    if (vec[i].key != NULL) free((char *)vec[i].key);

    switch (vec[i].type) {
      case GTT_PKVF_STRING_TOKEN:
        if (vec[i].val.str != NULL) free((char *)vec[i].val.str);
        break;

      case GTT_PKVF_STRING_VECTOR_TOKEN:
        if (vec[i].val.vec != NULL) {
          for (j = 0; j < cvector_size(vec[i].val.vec); j++) {
            if (vec[i].val.vec[j] != NULL) free(vec[i].val.vec[j]);
          }

          cvector_free(vec[i].val.vec);
        }
        break;
    }
  }

  cvector_free(vec);
}

cvector_vector_type(char *) pkvf_value_to_vec(const char *val) {
  char *el_ptr, *save_ptr, *el;
  cvector_vector_type(char *) vec;

  vec = NULL;

  el_ptr = strtok_r((char *)val, "@,@", &save_ptr);
  while (el_ptr != NULL) {
    if (strcmp(el_ptr, "") == 0) goto skip;

    el = calloc(strlen(el_ptr) + 1, sizeof(char));
    snprintf(el, strlen(el_ptr) + 1, "%s", el_ptr);
    cvector_push_back(vec, el);

  skip:
    el_ptr = strtok_r(NULL, "@,@", &save_ptr);
  }

  return vec;
}
