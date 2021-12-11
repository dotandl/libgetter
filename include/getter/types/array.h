/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_TYPES_ARRAY_H_
#define INCLUDE_GETTER_TYPES_ARRAY_H_

#define CVECTOR_LOGARITHMIC_GROWTH

#include <cvector.h>
#include <stddef.h>

GTT_HEADER_BEGIN

/** Represents array of const string. */
typedef struct GttCStrArr {
  const char **arr;
  size_t nmemb;  ///< Number of strings.
  size_t size;   ///< Size of each string.
} GttCStrArr;

/**
 * Creates new array of const strings.
 *
 * \param nmemb Number of strings in the array.
 * \param size Size of each string in the array.
 * \returns Array of const strings.
 * \see GttCStrArr
 */
GTT_API GttCStrArr gtt_cstr_arr_new(size_t nmemb, size_t size);

/**
 * Deletes existing array of const strings.
 *
 * \param self Array to delete.
 */
GTT_API void gtt_cstr_arr_delete(GttCStrArr self);

/**
 * Returns a number of elements in the array.
 *
 * \param arr Array to calculate number of elements from.
 * \returns Number of elements in the array.
 */
// TODO: remove
#define arrlen(arr) sizeof(arr) / sizeof(*arr)

GTT_HEADER_END

#endif /* INCLUDE_GETTER_TYPES_ARRAY_H_ */
