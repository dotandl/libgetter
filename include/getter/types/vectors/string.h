/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef TYPES_VECTORS_STRING_H_
#define TYPES_VECTORS_STRING_H_

#include <getter/decl.h>
#include <string.h>

HEADER_BEGIN

#define GTT_VEC_TYPE char*
#define GTT_VEC_NAME string
#define gtt_vec_compare_elements(el1, el2) strcmp((el1), (el2)) == 0

#include <getter/types/vector.h>

HEADER_END

#endif /* TYPES_VECTORS_STRING_H_ */
