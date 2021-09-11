/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#define PCRE2_CODE_UNIT_WIDTH 8

#include <getter/box/info.h>
#include <getter/tools/version.h>
#include <getter/types/array.h>
#include <jsmn.h>
#include <pcre2.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static bool json_str_eq(const char *json, jsmntok_t *token, const char *str);
static void json_str_alloc_copy(const char *json, jsmntok_t *token,
                                char **dest);
static void json_arr_to_vec(const char *json, jsmntok_t *token,
                            GttVector_string **vec);
static bool gtt_meets_version(const char *version);

GttBoxInfo *gtt_box_info_new_from_json(const char *json) {
  GttBoxInfo *bi;
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
    return NULL;  // error while parsing
  }

  if (res == 0 || tokens[0].type != JSMN_OBJECT) {
    free(tokens);
    return NULL;  // object expected
  }

  bi = malloc(sizeof(GttBoxInfo));
  memset(bi, 0, sizeof(GttBoxInfo));

  for (i = 1; i < res; i++) {
    if (json_str_eq(json, &tokens[i], "getter")) {  // STRINGS
      json_str_alloc_copy(json, &tokens[++i], (char **)&bi->getter);
    } else if (json_str_eq(json, &tokens[i], "name")) {
      json_str_alloc_copy(json, &tokens[++i], (char **)&bi->name);
    } else if (json_str_eq(json, &tokens[i], "full_name")) {
      json_str_alloc_copy(json, &tokens[++i], (char **)&bi->full_name);
    } else if (json_str_eq(json, &tokens[i], "summary")) {
      json_str_alloc_copy(json, &tokens[++i], (char **)&bi->summary);
    } else if (json_str_eq(json, &tokens[i], "description")) {
      json_str_alloc_copy(json, &tokens[++i], (char **)&bi->description);
    } else if (json_str_eq(json, &tokens[i], "homepage")) {
      json_str_alloc_copy(json, &tokens[++i], (char **)&bi->homepage);
    } else if (json_str_eq(json, &tokens[i], "repository")) {
      json_str_alloc_copy(json, &tokens[++i], (char **)&bi->repository);
    } else if (json_str_eq(json, &tokens[i], "license_name")) {
      json_str_alloc_copy(json, &tokens[++i], (char **)&bi->license_name);
    } else if (json_str_eq(json, &tokens[i], "license")) {
      json_str_alloc_copy(json, &tokens[++i], (char **)&bi->license);
    } else if (json_str_eq(json, &tokens[i], "readme")) {
      json_str_alloc_copy(json, &tokens[++i], (char **)&bi->readme);
    } else if (json_str_eq(json, &tokens[i], "changelog")) {
      json_str_alloc_copy(json, &tokens[++i], (char **)&bi->changelog);

    } else if (json_str_eq(json, &tokens[i], "authors")) {  // ARRAYS
      json_arr_to_vec(json, &tokens[++i], &bi->authors);
      i += tokens[i].size;
    } else if (json_str_eq(json, &tokens[i], "categories")) {
      json_arr_to_vec(json, &tokens[++i], &bi->categories);
      i += tokens[i].size;
    } else if (json_str_eq(json, &tokens[i], "dependencies")) {
      json_arr_to_vec(json, &tokens[++i], &bi->dependencies);
      i += tokens[i].size;
    } else if (json_str_eq(json, &tokens[i], "build_dependencies")) {
      json_arr_to_vec(json, &tokens[++i], &bi->build_dependencies);
      i += tokens[i].size;
    } else if (json_str_eq(json, &tokens[i], "optional_dependencies")) {
      json_arr_to_vec(json, &tokens[++i], &bi->optional_dependencies);
      i += tokens[i].size;
    } else if (json_str_eq(json, &tokens[i], "conflicts")) {
      json_arr_to_vec(json, &tokens[++i], &bi->conflicts);
      i += tokens[i].size;
    } else if (json_str_eq(json, &tokens[i], "replaces")) {
      json_arr_to_vec(json, &tokens[++i], &bi->replaces);
      i += tokens[i].size;
    } else {
      free(tokens);
      gtt_box_info_delete(bi);
      return NULL;  // unexpected token
    }
  }

  free(tokens);

  if (bi->name == NULL || bi->full_name == NULL || bi->summary == NULL ||
      bi->authors == NULL || bi->license_name == NULL) {
    gtt_box_info_delete(bi);
    return NULL;  // required fields missing
  }

  if (bi->getter != NULL && !gtt_meets_version(bi->getter)) {
    gtt_box_info_delete(bi);
    return NULL;  // libgetter's too old for this Box
  }

  return bi;
}

#define free_all_strings(vec, node)                             \
  if ((vec) != NULL)                                            \
  gtt_vector_for_each((vec), (node)) if ((node)->value != NULL) \
      free((node)->value)

void gtt_box_info_delete(GttBoxInfo *self) {
  GttVectorNode_string *node;

  if (self == NULL) return;

  if (self->getter != NULL) free((char **)self->getter);
  if (self->name != NULL) free((char **)self->name);
  if (self->full_name != NULL) free((char **)self->full_name);
  if (self->summary != NULL) free((char **)self->summary);
  if (self->description != NULL) free((char **)self->description);
  if (self->homepage != NULL) free((char **)self->homepage);
  if (self->repository != NULL) free((char **)self->repository);
  if (self->license_name != NULL) free((char **)self->license_name);
  if (self->license != NULL) free((char **)self->license);
  if (self->readme != NULL) free((char **)self->readme);
  if (self->changelog != NULL) free((char **)self->changelog);

  free_all_strings(self->authors, node);
  free_all_strings(self->categories, node);
  free_all_strings(self->dependencies, node);
  free_all_strings(self->build_dependencies, node);
  free_all_strings(self->optional_dependencies, node);
  free_all_strings(self->conflicts, node);
  free_all_strings(self->replaces, node);

  gtt_vector_string_delete(self->authors);
  gtt_vector_string_delete(self->categories);
  gtt_vector_string_delete(self->dependencies);
  gtt_vector_string_delete(self->build_dependencies);
  gtt_vector_string_delete(self->optional_dependencies);
  gtt_vector_string_delete(self->conflicts);
  gtt_vector_string_delete(self->replaces);

  free(self);
}

bool json_str_eq(const char *json, jsmntok_t *token, const char *str) {
  return token->type == JSMN_STRING &&
         token->end - token->start == strlen(str) &&
         strncmp(json + token->start, str, token->end - token->start) == 0;
}

void json_str_alloc_copy(const char *json, jsmntok_t *token, char **dest) {
  if (token->type != JSMN_STRING) return;

  *dest = calloc((token->end - token->start) + 1, sizeof(char));
  memcpy(*dest, json + token->start, token->end - token->start);
}

void json_arr_to_vec(const char *json, jsmntok_t *token,
                     GttVector_string **vec) {
  jsmntok_t *current_tok;
  char *buf;
  int i;

  if (token->type != JSMN_ARRAY) return;

  *vec = gtt_vector_string_new();

  for (i = 0; i < token->size; i++) {
    current_tok = token + i + 1;

    json_str_alloc_copy(json, current_tok, &buf);
    gtt_vector_string_push(*vec, buf);
  }
}

bool gtt_meets_version(const char *version) {
  pcre2_code *regexp;
  pcre2_match_data *match_data;
  PCRE2_SIZE error_offset;
  int error_code, matches;
  PCRE2_UCHAR buf[8];
  PCRE2_SIZE buflen;
  unsigned int major, minor, patch;

  regexp =
      pcre2_compile("^([0-9]+)\\.([0-9]+)\\.([0-9]+)$", PCRE2_ZERO_TERMINATED,
                    0, &error_code, &error_offset, NULL);

  if (regexp == NULL) return false;  // could not compile regexp

  match_data = pcre2_match_data_create_from_pattern(regexp, NULL);
  matches =
      pcre2_match(regexp, version, strlen(version), 0, 0, match_data, NULL);

  if (matches < 0) {
    pcre2_match_data_free(match_data);
    pcre2_code_free(regexp);
    return false;  // version not matched
  }

  buflen = arrlen(buf);
  pcre2_substring_copy_bynumber(match_data, 1, buf, &buflen);
  major = atoi(buf);

  buflen = arrlen(buf);
  pcre2_substring_copy_bynumber(match_data, 2, buf, &buflen);
  minor = atoi(buf);

  buflen = arrlen(buf);
  pcre2_substring_copy_bynumber(match_data, 3, buf, &buflen);
  patch = atoi(buf);

  pcre2_match_data_free(match_data);
  pcre2_code_free(regexp);

  return gtt_is_newer(GTT_VERSION_MAJOR, GTT_VERSION_MINOR, GTT_VERSION_PATCH,
                      major, minor, patch);
}
