/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef ARRAY_H_
#define ARRAY_H_

#include <getter/decl.h>
#include <vec.h>

HEADER_BEGIN

/**
 * Returns a number of elements in the array.
 *
 * \param arr Array to calculate number of elements from.
 * \returns Number of elements in the array.
 */
#define arrlen(arr) sizeof(arr) / sizeof(*arr)

HEADER_END

#endif /* ARRAY_H_ */
