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

#include <cvector.h>
#include <json-c/json.h>

GTT_HEADER_BEGIN

/**
 * Copies the string of `key` from JSON object `obj` to `buf` of size `buflen`.
 *
 * \param obj JSON object to copy the string from.
 * \param key The key of the string to copy.
 * \param buf The destination string buffer.
 * \param buflen The size of `buf`.
 */
GTT_API void gtt_copy_str_from_json(json_object *obj, const char *key,
                                    char *buf, size_t buflen);

/**
 * Copies the string array of `key` from JSON object `obj` to string vector
 * `vec`.
 *
 * \param obj JSON object containing the array to copy.
 * \param key The key of the array to copy.
 * \param vec A pointer to the destination string vector.
 */
GTT_API void gtt_copy_arr_from_json(json_object *obj, const char *key,
                                    cvector_vector_type(char *) * vec);

GTT_HEADER_END

#endif /* INCLUDE_GETTER_TYPES_JSON_H_ */
