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
#include <getter/tools/error.h>
#include <getter/tools/version.h>
#include <getter/types/array.h>
#include <getter/types/json.h>
#include <pcre2.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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
    gtt_error(GTT_PARSE_ERROR, "Error parsing JSON string");
    return NULL;
  }

  if (res == 0 || tokens[0].type != JSMN_OBJECT) {
    free(tokens);
    gtt_error(GTT_PARSE_ERROR,
              "Not a valid Box JSON - expected object as root token");
    return NULL;
  }

  bi = malloc(sizeof(GttBoxInfo));
  memset(bi, 0, sizeof(GttBoxInfo));

  gtt_ok();  // If all JSON read successfully, error code will be GTT_OK

  for (i = 1; i < res; i++) {
    // STRINGS
    if (gtt_json_str_eq(json, tokens[i], "getter")) {
      gtt_json_str_copy(json, tokens[++i], (char *)bi->getter, GTT_BUFLEN);
    } else if (gtt_json_str_eq(json, tokens[i], "name")) {
      gtt_json_str_copy(json, tokens[++i], (char *)bi->name, GTT_BUFLEN);
    } else if (gtt_json_str_eq(json, tokens[i], "full_name")) {
      gtt_json_str_copy(json, tokens[++i], (char *)bi->full_name, GTT_BUFLEN);
    } else if (gtt_json_str_eq(json, tokens[i], "summary")) {
      gtt_json_str_copy(json, tokens[++i], (char *)bi->summary, GTT_BUFLEN);
    } else if (gtt_json_str_eq(json, tokens[i], "description")) {
      gtt_json_str_copy(json, tokens[++i], (char *)bi->description, GTT_BUFLEN);
    } else if (gtt_json_str_eq(json, tokens[i], "homepage")) {
      gtt_json_str_copy(json, tokens[++i], (char *)bi->homepage, GTT_BUFLEN);
    } else if (gtt_json_str_eq(json, tokens[i], "repository")) {
      gtt_json_str_copy(json, tokens[++i], (char *)bi->repository, GTT_BUFLEN);
    } else if (gtt_json_str_eq(json, tokens[i], "license_name")) {
      gtt_json_str_copy(json, tokens[++i], (char *)bi->license_name,
                        GTT_BUFLEN);
    } else if (gtt_json_str_eq(json, tokens[i], "license")) {
      gtt_json_str_copy(json, tokens[++i], (char *)bi->license, GTT_BUFLEN);
    } else if (gtt_json_str_eq(json, tokens[i], "readme")) {
      gtt_json_str_copy(json, tokens[++i], (char *)bi->readme, GTT_BUFLEN);
    } else if (gtt_json_str_eq(json, tokens[i], "changelog")) {
      gtt_json_str_copy(json, tokens[++i], (char *)bi->changelog, GTT_BUFLEN);

      // ARRAYS
    } else if (gtt_json_str_eq(json, tokens[i], "authors")) {
      gtt_json_arr_to_vec(json, &tokens[++i], &bi->authors);
      i += tokens[i].size;
    } else if (gtt_json_str_eq(json, tokens[i], "categories")) {
      gtt_json_arr_to_vec(json, &tokens[++i], &bi->categories);
      i += tokens[i].size;
    } else if (gtt_json_str_eq(json, tokens[i], "dependencies")) {
      gtt_json_arr_to_vec(json, &tokens[++i], &bi->dependencies);
      i += tokens[i].size;
    } else if (gtt_json_str_eq(json, tokens[i], "build_dependencies")) {
      gtt_json_arr_to_vec(json, &tokens[++i], &bi->build_dependencies);
      i += tokens[i].size;
    } else if (gtt_json_str_eq(json, tokens[i], "optional_dependencies")) {
      gtt_json_arr_to_vec(json, &tokens[++i], &bi->optional_dependencies);
      i += tokens[i].size;
    } else if (gtt_json_str_eq(json, tokens[i], "conflicts")) {
      gtt_json_arr_to_vec(json, &tokens[++i], &bi->conflicts);
      i += tokens[i].size;
    } else if (gtt_json_str_eq(json, tokens[i], "replaces")) {
      gtt_json_arr_to_vec(json, &tokens[++i], &bi->replaces);
      i += tokens[i].size;

      // UNEXPECTED FIELD
    } else {
      gtt_error(GTT_INVALID_DATA, "Not a valid Box JSON - unexpected token");
    }
  }

  free(tokens);

  // Check if there were any errors while parsing JSON
  if (GTT_FAILED) {
    // Error is already set, no need to set it again
    gtt_box_info_delete(bi);
    return NULL;
  }

  if (bi->name[0] == 0 || bi->full_name[0] == 0 || bi->summary[0] == 0 ||
      bi->authors == NULL || bi->license_name[0] == 0) {
    gtt_box_info_delete(bi);

    gtt_error(GTT_PARSE_ERROR,
              "Not a valid Box JSON - some of the required fields are missing");
    return NULL;
  }

  if (bi->getter[0] != 0 && !gtt_meets_version(bi->getter)) {
    gtt_box_info_delete(bi);

    gtt_error(GTT_LIBGETTER_TOO_OLD, "libgetter is too old for this Box");
    return NULL;
  }

  gtt_ok();
  return bi;
}

#define free_all_strings(vec)                 \
  do {                                        \
    int i;                                    \
    if ((vec) != NULL)                        \
      for (i = 0; i < cvector_size(vec); i++) \
        if ((vec)[i] != NULL) free((vec)[i]); \
  } while (0)

void gtt_box_info_delete(GttBoxInfo *self) {
  if (self == NULL) return;

  free_all_strings(self->authors);
  free_all_strings(self->categories);
  free_all_strings(self->dependencies);
  free_all_strings(self->build_dependencies);
  free_all_strings(self->optional_dependencies);
  free_all_strings(self->conflicts);
  free_all_strings(self->replaces);

  cvector_free(self->authors);
  cvector_free(self->categories);
  cvector_free(self->dependencies);
  cvector_free(self->build_dependencies);
  cvector_free(self->optional_dependencies);
  cvector_free(self->conflicts);
  cvector_free(self->replaces);

  free(self);
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
