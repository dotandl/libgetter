/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include "cppvector.h"

void cppvector_push_back(cvector_vector_type(void *) * vec, void *obj) {
  cvector_push_back((*vec), (obj));
}
