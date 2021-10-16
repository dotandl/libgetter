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

HEADER_BEGIN

WINDLL bool gtt_json_str_eq(const char *json, jsmntok_t *token,
                            const char *str);
WINDLL void gtt_json_str_alloc_copy(const char *json, jsmntok_t *token,
                                    char **dest);
WINDLL void gtt_json_arr_to_vec(const char *json, jsmntok_t *token,
                                cvector_vector_type(char *) * vec);

HEADER_END

#endif /* INCLUDE_GETTER_TYPES_JSON_H_ */
