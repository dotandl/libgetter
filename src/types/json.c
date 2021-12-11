/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/types/json.h>
#include <stdio.h>

void gtt_copy_str_from_json(json_object *obj, const char *key, char *buf,
                            size_t buflen) {
  json_object *val;

  if (json_object_object_get_ex(obj, key, &val) &&
      json_object_is_type(val, json_type_string))
    snprintf(buf, buflen, "%s", json_object_get_string(val));
}

void gtt_copy_arr_from_json(json_object *obj, const char *key,
                            GttCStrArr *arr) {
  json_object *arr_val, *val;
  size_t arr_len, i;

  if (json_object_object_get_ex(obj, key, &arr_val) &&
      json_object_is_type(arr_val, json_type_array)) {
    arr_len = json_object_array_length(arr_val);
    *arr = gtt_cstr_arr_new(arr_len, GTT_BUFLEN);

    for (i = 0; i < arr_len; i++) {
      val = json_object_array_get_idx(arr_val, i);

      snprintf((char *)arr->arr[i], GTT_BUFLEN, "%s",
               json_object_get_string(val));
    }
  }
}
