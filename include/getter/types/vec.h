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

/**
 * Frees every dynamically-allocated string in dynamically-allocated string
 * vector.
 *
 * \param vec String vector to free.
 */
WINDLL void vec_str_free(vec_str_t *vec);

HEADER_END

#endif /* VEC_H_ */
