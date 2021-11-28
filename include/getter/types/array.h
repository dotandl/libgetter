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

GTT_HEADER_BEGIN

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
static inline void gtt_free_str_vec(cvector_vector_type(char *) vec) {
  unsigned int i;

  if (vec == NULL) return;
  for (i = 0; i < cvector_size(vec); i++) free(vec[i]);
  cvector_free(vec);
}

GTT_HEADER_END

#endif /* INCLUDE_GETTER_TYPES_ARRAY_H_ */
