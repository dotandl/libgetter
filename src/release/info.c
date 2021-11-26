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

static void pkvf_str_alloc_copy(GttPKVFToken *token, char **dest);
static void pkvf_arr_to_vec(GttPKVFToken *token,
                            cvector_vector_type(char *) * vec);

GttReleaseInfo *gtt_release_info_new_from_pkvf(const char *pkvf) {
  GttReleaseInfo *self;
  GttPKVFToken *token;
  cvector_vector_type(GttPKVFToken) vec;
  int i;

  vec = gtt_parse_pkvf(pkvf);
  if (GTT_FAILED) return NULL;  // forward the error

  self = malloc(sizeof(GttReleaseInfo));
  memset(self, 0, sizeof(GttReleaseInfo));

  for (i = 0; i < cvector_size(vec); i++) {
    token = &vec[i];

    switch (token->type) {
      case GTT_PKVF_STRING_TOKEN:
        if (strcmp(token->key, "script") == 0) {
          pkvf_str_alloc_copy(token, (char **)&self->script);
        } else if (strcmp(token->key, "repository") == 0) {
          pkvf_str_alloc_copy(token, (char **)&self->repository);
        } else if (strcmp(token->key, "license_name") == 0) {
          pkvf_str_alloc_copy(token, (char **)&self->license_name);
        } else if (strcmp(token->key, "license") == 0) {
          pkvf_str_alloc_copy(token, (char **)&self->license);
        } else if (strcmp(token->key, "readme") == 0) {
          pkvf_str_alloc_copy(token, (char **)&self->readme);
        } else if (strcmp(token->key, "changelog") == 0) {
          pkvf_str_alloc_copy(token, (char **)&self->changelog);
        } else {
          gtt_vector_pkvf_token_free(vec);
          gtt_release_info_delete(self);

          gtt_error(GTT_INVALID_DATA, "Unexpected token found");
          return NULL;
        }
        break;

      case GTT_PKVF_STRING_VECTOR_TOKEN:
        if (strcmp(token->key, "dependencies") == 0) {
          pkvf_arr_to_vec(token, &self->dependencies);
        } else if (strcmp(token->key, "build_dependencies") == 0) {
          pkvf_arr_to_vec(token, &self->build_dependencies);
        } else if (strcmp(token->key, "optional_dependencies") == 0) {
          pkvf_arr_to_vec(token, &self->optional_dependencies);
        } else if (strcmp(token->key, "conflicts") == 0) {
          pkvf_arr_to_vec(token, &self->conflicts);
        } else if (strcmp(token->key, "replaces") == 0) {
          pkvf_arr_to_vec(token, &self->replaces);
        } else {
          gtt_vector_pkvf_token_free(vec);
          gtt_release_info_delete(self);

          gtt_error(GTT_INVALID_DATA, "Unexpected token found");
          return NULL;
        }
        break;
    }
  }

  gtt_vector_pkvf_token_free(vec);

  if (self->script == NULL) {
    gtt_release_info_delete(self);
    gtt_error(GTT_PARSE_ERROR, "Some of the required fields is missing");
    return NULL;
  }

  gtt_ok();
  return self;
}

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
      gtt_json_str_alloc_copy(json, &tokens[++i], (char **)&ri->script);
    } else if (gtt_json_str_eq(json, &tokens[i], "repository")) {
      gtt_json_str_alloc_copy(json, &tokens[++i], (char **)&ri->repository);
    } else if (gtt_json_str_eq(json, &tokens[i], "license_name")) {
      gtt_json_str_alloc_copy(json, &tokens[++i], (char **)&ri->license_name);
    } else if (gtt_json_str_eq(json, &tokens[i], "license")) {
      gtt_json_str_alloc_copy(json, &tokens[++i], (char **)&ri->license);
    } else if (gtt_json_str_eq(json, &tokens[i], "readme")) {
      gtt_json_str_alloc_copy(json, &tokens[++i], (char **)&ri->readme);
    } else if (gtt_json_str_eq(json, &tokens[i], "changelog")) {
      gtt_json_str_alloc_copy(json, &tokens[++i], (char **)&ri->changelog);

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

  if (ri->script == NULL) {
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

  if (self->script != NULL) free((char *)self->script);
  if (self->repository != NULL) free((char *)self->repository);
  if (self->license_name != NULL) free((char *)self->license_name);
  if (self->license != NULL) free((char *)self->license);
  if (self->readme != NULL) free((char *)self->readme);
  if (self->changelog != NULL) free((char *)self->changelog);

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

void pkvf_str_alloc_copy(GttPKVFToken *token, char **dest) {
  *dest = calloc(strlen(token->val.str) + 1, sizeof(char));
  snprintf(*dest, strlen(token->val.str) + 1, "%s", token->val.str);
}

void pkvf_arr_to_vec(GttPKVFToken *token, cvector_vector_type(char *) * vec) {
  int i;
  char *str;

  *vec = NULL;

  for (i = 0; i < cvector_size(token->val.vec); i++) {
    str = calloc(strlen(token->val.vec[i]) + 1, sizeof(char));
    snprintf(str, strlen(token->val.vec[i]) + 1, "%s", token->val.vec[i]);

    // *vec needs to be surrounded by () because of bug in the c-vector lib
    cvector_push_back((*vec), str);
  }
}
