/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/tools/error.h>
#include <getter/types/pkvf.h>
#include <stdio.h>
#include <string.h>

static GttVector_string *pkvf_value_to_vec(const char *val);

GttVector_pkvf_token *gtt_parse_pkvf(const char *pkvf) {
  size_t key_len, val_len;
  char *line_ptr, *save_ptr, *seq_ptr, *key, *val;
  GttVector_pkvf_token *vec;
  GttVector_string *vals;
  GttPKVFToken token;
  GttPKVFTokenValue token_value;

  vec = gtt_vector_pkvf_token_new();

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

    gtt_vector_pkvf_token_push(vec, token);

  skip:
    line_ptr = strtok_r(NULL, "\n", &save_ptr);
  }

  gtt_ok();
  return vec;
}

void gtt_vector_pkvf_token_free(GttVector_pkvf_token *vec) {
  GttVectorNode_pkvf_token *node_pkvf;
  GttVectorNode_string *node_str;

  if (vec == NULL) return;

  gtt_vector_for_each(vec, node_pkvf) {
    if (node_pkvf->value.key != NULL) free((char *)node_pkvf->value.key);

    switch (node_pkvf->value.type) {
      case GTT_PKVF_STRING_TOKEN:
        if (node_pkvf->value.val.str != NULL)
          free((char *)node_pkvf->value.val.str);
        break;

      case GTT_PKVF_STRING_VECTOR_TOKEN:
        if (node_pkvf->value.val.vec != NULL) {
          gtt_vector_for_each(node_pkvf->value.val.vec, node_str) {
            if (node_str->value != NULL) free(node_str->value);
          }

          gtt_vector_string_delete(node_pkvf->value.val.vec);
        }
        break;
    }
  }

  gtt_vector_pkvf_token_delete(vec);
}

GttVector_string *pkvf_value_to_vec(const char *val) {
  char *el_ptr, *save_ptr, *el;
  GttVector_string *vec;

  vec = gtt_vector_string_new();

  el_ptr = strtok_r((char *)val, "@,@", &save_ptr);
  while (el_ptr != NULL) {
    if (strcmp(el_ptr, "") == 0) goto skip;

    el = calloc(strlen(el_ptr) + 1, sizeof(char));
    strcpy(el, el_ptr);
    gtt_vector_string_push(vec, el);

  skip:
    el_ptr = strtok_r(NULL, "@,@", &save_ptr);
  }

  return vec;
}
