/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <jsmn.h>
//
#include <getter/tools/error.h>
#include <getter/types/json.h>
#include <string.h>

bool gtt_json_str_eq(const char *json, jsmntok_t *token, const char *str) {
  return token->type == JSMN_STRING &&
         token->end - token->start == strlen(str) &&
         strncmp(json + token->start, str, token->end - token->start) == 0;
}

void gtt_json_str_alloc_copy(const char *json, jsmntok_t *token, char **dest) {
  if (token->type != JSMN_STRING) {
    gtt_error(GTT_PARSE_ERROR,
              "Not a valid JSON - found a token with incorrect type");
    return;
  }

  *dest = calloc((token->end - token->start) + 1, sizeof(char));
  memcpy(*dest, json + token->start, token->end - token->start);
}

void gtt_json_arr_to_vec(const char *json, jsmntok_t *token,
                         cvector_vector_type(char *) * vec) {
  jsmntok_t *current_tok;
  char *buf;
  int i;

  if (token->type != JSMN_ARRAY) {
    gtt_error(GTT_PARSE_ERROR,
              "Not a valid JSON - found a token with incorrect type");
    return;
  }

  *vec = NULL;

  for (i = 0; i < token->size; i++) {
    current_tok = token + i + 1;

    gtt_json_str_alloc_copy(json, current_tok, &buf);

    // *vec needs to be surrounded by () because of bug in the c-vector lib
    cvector_push_back((*vec), buf);
  }
}
