/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef VEC_H_
#define VEC_H_

#include <getter/decl.h>
#include <vec.h>

HEADER_BEGIN

/** Key-value pair, useful in vectors. */
struct GttKeyVal {
  char *key;
  void *val;
};

typedef struct GttKeyVal GttKeyVal;
typedef vec_t(GttKeyVal) vec_keyval_t;

/**
 * Frees every dynamically-allocated string in dynamically-allocated string
 * vector.
 *
 * \param vec String vector to free.
 */
WINDLL void vec_str_free(vec_str_t *vec);

/**
 * Frees every key-value pair in dynamically-allocated key-value vector.
 *
 * \param vec Key-value vector to free.
 */
WINDLL void vec_keyval_free(vec_keyval_t *vec);

HEADER_END

#endif /* VEC_H_ */
