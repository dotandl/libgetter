/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

/**
 * \file cppvector.h
 * File containing C++ "polyfills" for `c-vector` library.
 *
 * C++ doesn't like pointer casting so using `c-vector` can cause some weird
 * errors. These errors most often look like `invalid convertion from void* to
 * sometype*`. This file and `cppvector.c` fix these errors with a function
 * written in C (which is also accessible in C++) which uses the `c-vector`'s
 * macros.
 */

#ifndef TESTS_CPPVECTOR_H_
#define TESTS_CPPVECTOR_H_

#define CVECTOR_LOGARITHMIC_GROWTH

#include <cvector.h>
#include <getter/release/release.h>

#ifdef __cplusplus
extern "C" {
#endif

void cppvector_push_back(cvector_vector_type(void *) * vec, void *obj);

#ifdef __cplusplus
}
#endif

#endif /* TESTS_CPPVECTOR_H_ */
