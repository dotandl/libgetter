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

typedef struct GttCStrArr {
  const char **arr;
  size_t nmemb;
  size_t size;
} GttCStrArr;

static inline GttCStrArr gtt_cstr_arr_new(size_t nmemb, size_t size) {
  char **ptr;
  size_t i;

  /* Allocate array of pointers on the heap */
  ptr = (char **)calloc(nmemb, sizeof(char *));

  /* Allocate arrays of chars (strings) and put them in the array of pointers */
  for (i = 0; i < nmemb; i++) {
    ptr[i] = (char *)calloc(size, sizeof(char));
  }

  return (GttCStrArr){(const char **)ptr, nmemb, size};
}

static inline void gtt_cstr_arr_delete(GttCStrArr self) {
  size_t i;

  /* Free arrays of chars (strings) */
  for (i = 0; i < self.nmemb; i++) free((void *)self.arr[i]);

  /* Free array of pointers */
  free(self.arr);
}

/**
 * Returns a number of elements in the array.
 *
 * \param arr Array to calculate number of elements from.
 * \returns Number of elements in the array.
 */
#define arrlen(arr) sizeof(arr) / sizeof(*arr)

/**
 * Frees the string vector `vec` and all strings it contains.
 *
 * \param vec Vector of strings to free.
 */
// static inline void gtt_free_str_vec(cvector_vector_type(char *) vec) {
//   unsigned int i;

//   if (vec == NULL) return;
//   for (i = 0; i < cvector_size(vec); i++) free(vec[i]);
//   cvector_free(vec);
// }

GTT_HEADER_END

#endif /* INCLUDE_GETTER_TYPES_ARRAY_H_ */
