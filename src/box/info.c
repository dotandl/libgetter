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
  json_object *jsonobj;
  enum json_tokener_error err;

  jsonobj = json_tokener_parse_verbose(json, &err);
  if (err != json_tokener_success) {
    gtt_error(GTT_PARSE_ERROR, "Error parsing JSON string");
    return NULL;
  }

  if (!json_object_is_type(jsonobj, json_type_object)) {
    json_object_put(jsonobj);

    gtt_error(GTT_PARSE_ERROR,
              "Not a valid Release JSON - expected object as root token");
    return NULL;
  }

  bi = malloc(sizeof(GttBoxInfo));
  memset(bi, 0, sizeof(GttBoxInfo));

  gtt_copy_str_from_json(jsonobj, "getter", (char *)bi->getter, GTT_BUFLEN);
  gtt_copy_str_from_json(jsonobj, "name", (char *)bi->name, GTT_BUFLEN);
  gtt_copy_str_from_json(jsonobj, "full_name", (char *)bi->full_name,
                         GTT_BUFLEN);
  gtt_copy_str_from_json(jsonobj, "summary", (char *)bi->summary, GTT_BUFLEN);
  gtt_copy_str_from_json(jsonobj, "description", (char *)bi->description,
                         GTT_BUFLEN);
  gtt_copy_str_from_json(jsonobj, "homepage", (char *)bi->homepage, GTT_BUFLEN);
  gtt_copy_str_from_json(jsonobj, "repository", (char *)bi->repository,
                         GTT_BUFLEN);
  gtt_copy_str_from_json(jsonobj, "license_name", (char *)bi->license_name,
                         GTT_BUFLEN);
  gtt_copy_str_from_json(jsonobj, "license", (char *)bi->license, GTT_BUFLEN);
  gtt_copy_str_from_json(jsonobj, "readme", (char *)bi->readme, GTT_BUFLEN);
  gtt_copy_str_from_json(jsonobj, "changelog", (char *)bi->changelog,
                         GTT_BUFLEN);

  gtt_copy_arr_from_json(jsonobj, "authors", &bi->authors);
  gtt_copy_arr_from_json(jsonobj, "categories", &bi->categories);
  gtt_copy_arr_from_json(jsonobj, "dependencies", &bi->dependencies);
  gtt_copy_arr_from_json(jsonobj, "build_dependencies",
                         &bi->build_dependencies);
  gtt_copy_arr_from_json(jsonobj, "optional_dependencies",
                         &bi->optional_dependencies);
  gtt_copy_arr_from_json(jsonobj, "conflicts", &bi->conflicts);
  gtt_copy_arr_from_json(jsonobj, "replaces", &bi->replaces);

  if (bi->name[0] == 0 || bi->full_name[0] == 0 || bi->summary[0] == 0 ||
      bi->authors.nmemb == 0 || bi->license_name[0] == 0) {
    gtt_box_info_delete(bi);
    json_object_put(jsonobj);

    gtt_error(GTT_PARSE_ERROR,
              "Not a valid Box JSON - some of the required fields are missing");
    return NULL;
  }

  if (bi->getter[0] != 0 && !gtt_meets_version(bi->getter)) {
    gtt_box_info_delete(bi);
    json_object_put(jsonobj);

    gtt_error(GTT_LIBGETTER_TOO_OLD, "libgetter is too old for this Box");
    return NULL;
  }

  json_object_put(jsonobj);
  gtt_ok();
  return bi;
}

void gtt_box_info_delete(GttBoxInfo *self) {
  if (self == NULL) return;

  gtt_cstr_arr_delete(self->authors);
  gtt_cstr_arr_delete(self->categories);
  gtt_cstr_arr_delete(self->dependencies);
  gtt_cstr_arr_delete(self->build_dependencies);
  gtt_cstr_arr_delete(self->optional_dependencies);
  gtt_cstr_arr_delete(self->conflicts);
  gtt_cstr_arr_delete(self->replaces);

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
