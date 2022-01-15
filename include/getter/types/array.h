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

#include <stddef.h>
#include <stdlib.h>

GTT_HEADER_BEGIN

/** Represents array of const string. */
typedef struct GttCStrArr {
  const char **arr;
  size_t nmemb;  ///< Number of strings.
  size_t size;   ///< Size of each string.
} GttCStrArr;

/** Represents an array of pointers. */
typedef struct GttPtrArr {
  void **arr;
  size_t nmemb;
} GttPtrArr;

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
 * Creates new array of pointers.
 *
 * \param nmemb Number of pointers in the array.
 * \returns Array of pointers
 * \see GttPtrArr
 */
GTT_API GttPtrArr gtt_ptr_arr_new(size_t nmemb);

/**
 * Reallocates the array of pointers in case to add more space to it.
 *
 * \param self Pointer to the array of pointers to resize.
 * \param nmemb New number of pointers in the array (must be greater than the
 * current nmemb) or -1 to increment the current nmemb.
 * \see GttPtrArr
 */
GTT_API void gtt_ptr_arr_resize(GttPtrArr *self, int nmemb);

/**
 * Deletes the array of pointers.
 *
 * Note that this macro does not free any of pointers in the array. If you
 * want to do so call `gtt_ptr_arr_delete_all` instead.
 *
 * \param self Array of pointers to delete.
 * \see GttPtrArr
 * \see gtt_ptr_arr_delete_all
 */
#define gtt_ptr_arr_delete(self) free(self.arr)

/**
 * Frees each pointer in the array of pointers and deletes the array itself.
 *
 * Do not call this function when at least one pointer in the array isn't
 * heap-allocated. In such case `gtt_ptr_arr_delete` should be used instead.
 *
 * \param self Array of pointers to delete.
 * \see GttPtrArr
 * \see gtt_ptr_arr_delete
 */
GTT_API void gtt_ptr_arr_delete_all(GttPtrArr self);

GTT_HEADER_END

#endif /* INCLUDE_GETTER_TYPES_ARRAY_H_ */
