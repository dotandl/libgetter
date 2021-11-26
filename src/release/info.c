/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/release/info.h>
#include <getter/tools/error.h>
#include <getter/types/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GttReleaseInfo *gtt_release_info_new_from_json(const char *json) {
  GttReleaseInfo *ri;
  jsmn_parser parser;
  jsmntok_t *tokens;
  size_t tokens_count;
  int res, i;

  jsmn_init(&parser);

  tokens_count = 32;
  tokens = calloc(tokens_count, sizeof(jsmntok_t));
  res = jsmn_parse(&parser, json, strlen(json), tokens, tokens_count);

  while (res == JSMN_ERROR_NOMEM) {
    tokens_count += 32;
    tokens = realloc(tokens, sizeof(jsmntok_t) * tokens_count);
    res = jsmn_parse(&parser, json, strlen(json), tokens, tokens_count);
  }

  if (res == JSMN_ERROR_INVAL || res == JSMN_ERROR_PART) {
    free(tokens);
    gtt_error(GTT_PARSE_ERROR, "Error parsing JSON string");
    return NULL;
  }

  // `res` contains number of found tokens
  if (res == 0 || tokens[0].type != JSMN_OBJECT) {
    free(tokens);
    gtt_error(GTT_PARSE_ERROR,
              "Not a valid Release JSON - expected object as root token");
    return NULL;
  }

  ri = malloc(sizeof(GttReleaseInfo));
  memset(ri, 0, sizeof(GttReleaseInfo));

  gtt_ok();  // If all JSON read successfully, error code will be GTT_OK

  for (i = 1; i < res; i++) {
    // STRINGS
    if (gtt_json_str_eq(json, &tokens[i], "script")) {
      gtt_json_str_copy(json, tokens[++i], (char *)ri->script, GTT_BUFLEN);
    } else if (gtt_json_str_eq(json, &tokens[i], "repository")) {
      gtt_json_str_copy(json, tokens[++i], (char *)ri->repository, GTT_BUFLEN);
    } else if (gtt_json_str_eq(json, &tokens[i], "license_name")) {
      gtt_json_str_copy(json, tokens[++i], (char *)ri->license_name,
                        GTT_BUFLEN);
    } else if (gtt_json_str_eq(json, &tokens[i], "license")) {
      gtt_json_str_copy(json, tokens[++i], (char *)ri->license, GTT_BUFLEN);
    } else if (gtt_json_str_eq(json, &tokens[i], "readme")) {
      gtt_json_str_copy(json, tokens[++i], (char *)ri->readme, GTT_BUFLEN);
    } else if (gtt_json_str_eq(json, &tokens[i], "changelog")) {
      gtt_json_str_copy(json, tokens[++i], (char *)ri->changelog, GTT_BUFLEN);

      // ARRAYS
    } else if (gtt_json_str_eq(json, &tokens[i], "dependencies")) {
      gtt_json_arr_to_vec(json, &tokens[++i], &ri->dependencies);
      i += tokens[i].size;
    } else if (gtt_json_str_eq(json, &tokens[i], "build_dependencies")) {
      gtt_json_arr_to_vec(json, &tokens[++i], &ri->build_dependencies);
      i += tokens[i].size;
    } else if (gtt_json_str_eq(json, &tokens[i], "optional_dependencies")) {
      gtt_json_arr_to_vec(json, &tokens[++i], &ri->optional_dependencies);
      i += tokens[i].size;
    } else if (gtt_json_str_eq(json, &tokens[i], "conflicts")) {
      gtt_json_arr_to_vec(json, &tokens[++i], &ri->conflicts);
      i += tokens[i].size;
    } else if (gtt_json_str_eq(json, &tokens[i], "replaces")) {
      gtt_json_arr_to_vec(json, &tokens[++i], &ri->replaces);
      i += tokens[i].size;

      // UNEXPECTED FIELD
    } else {
      gtt_error(GTT_INVALID_DATA,
                "Not a valid Release JSON - unexpected token");
    }
  }

  free(tokens);

  // Check if there were any errors while parsing JSON
  if (GTT_FAILED) {
    // Error is already set, no need to set it again
    gtt_release_info_delete(ri);
    return NULL;
  }

  if (ri->script[0] == 0) {
    gtt_release_info_delete(ri);
    gtt_error(
        GTT_PARSE_ERROR,
        "Not a valid Release JSON - some of the required fields are missing");

    return NULL;
  }

  gtt_ok();
  return ri;
}

#define free_all_strings(vec)                 \
  do {                                        \
    int i;                                    \
    if ((vec) != NULL)                        \
      for (i = 0; i < cvector_size(vec); i++) \
        if ((vec)[i] != NULL) free((vec)[i]); \
  } while (0)

void gtt_release_info_delete(GttReleaseInfo *self) {
  if (self == NULL) return;

  free_all_strings(self->dependencies);
  free_all_strings(self->build_dependencies);
  free_all_strings(self->optional_dependencies);
  free_all_strings(self->conflicts);
  free_all_strings(self->replaces);

  cvector_free(self->dependencies);
  cvector_free(self->build_dependencies);
  cvector_free(self->optional_dependencies);
  cvector_free(self->conflicts);
  cvector_free(self->replaces);

  free(self);
}
