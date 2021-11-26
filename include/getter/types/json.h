/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_TYPES_JSON_H_
#define INCLUDE_GETTER_TYPES_JSON_H_

#define CVECTOR_LOGARITHMIC_GROWTH
#define JSMN_HEADER

#include <cvector.h>
#include <jsmn.h>
#include <stdbool.h>

GTT_HEADER_BEGIN

GTT_API bool gtt_json_str_eq(const char *json, jsmntok_t token,
                             const char *str);
GTT_API void gtt_json_str_copy(const char *json, jsmntok_t token, char *dest,
                               size_t buflen);
GTT_API void gtt_json_str_alloc_copy(const char *json, jsmntok_t token,
                                     char **dest);
GTT_API void gtt_json_arr_to_vec(const char *json, jsmntok_t *token,
                                 cvector_vector_type(char *) * vec);

GTT_HEADER_END

#endif /* INCLUDE_GETTER_TYPES_JSON_H_ */
