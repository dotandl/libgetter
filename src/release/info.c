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
#include <getter/types/array.h>
#include <getter/types/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GttReleaseInfo *gtt_release_info_new_from_json(const char *json) {
  GttReleaseInfo *ri;
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

  ri = malloc(sizeof(GttReleaseInfo));
  memset(ri, 0, sizeof(GttReleaseInfo));

  gtt_copy_str_from_json(jsonobj, "script", (char *)ri->script, GTT_BUFLEN);
  gtt_copy_str_from_json(jsonobj, "repository", (char *)ri->repository,
                         GTT_BUFLEN);
  gtt_copy_str_from_json(jsonobj, "license_name", (char *)ri->license_name,
                         GTT_BUFLEN);
  gtt_copy_str_from_json(jsonobj, "license", (char *)ri->license, GTT_BUFLEN);
  gtt_copy_str_from_json(jsonobj, "readme", (char *)ri->readme, GTT_BUFLEN);
  gtt_copy_str_from_json(jsonobj, "changelog", (char *)ri->changelog,
                         GTT_BUFLEN);

  gtt_copy_arr_from_json(jsonobj, "dependencies", &ri->dependencies);
  gtt_copy_arr_from_json(jsonobj, "build_dependencies",
                         &ri->build_dependencies);
  gtt_copy_arr_from_json(jsonobj, "optional_dependencies",
                         &ri->optional_dependencies);
  gtt_copy_arr_from_json(jsonobj, "conflicts", &ri->conflicts);
  gtt_copy_arr_from_json(jsonobj, "replaces", &ri->replaces);

  if (ri->script[0] == 0) {
    gtt_release_info_delete(ri);
    json_object_put(jsonobj);

    gtt_error(
        GTT_PARSE_ERROR,
        "Not a valid Release JSON - some of the required fields are missing");

    return NULL;
  }

  json_object_put(jsonobj);
  gtt_ok();
  return ri;
}

void gtt_release_info_delete(GttReleaseInfo *self) {
  if (self == NULL) return;

  gtt_cstr_arr_delete(self->dependencies);
  gtt_cstr_arr_delete(self->build_dependencies);
  gtt_cstr_arr_delete(self->optional_dependencies);
  gtt_cstr_arr_delete(self->conflicts);
  gtt_cstr_arr_delete(self->replaces);

  free(self);
}
