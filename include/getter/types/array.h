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

GTT_HEADER_BEGIN

/**
 * Returns a number of elements in the array.
 *
 * \param arr Array to calculate number of elements from.
 * \returns Number of elements in the array.
 */
#define arrlen(arr) sizeof(arr) / sizeof(*arr)

GTT_HEADER_END

#endif /* INCLUDE_GETTER_TYPES_ARRAY_H_ */
