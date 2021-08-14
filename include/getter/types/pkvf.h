/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef TYPES_PKVF_H_
#define TYPES_PKVF_H_

#include <getter/decl.h>
#include <stdbool.h>
#include <string.h>

HEADER_BEGIN

#define GTT_VEC_TYPE char *
#define GTT_VEC_NAME string
#define gtt_vec_compare_elements(el1, el2) strcmp(el1, el2) == 0
#include <getter/types/vector.h>

enum GttPKVFTokenType { GTT_PKVF_STRING_TOKEN, GTT_PKVF_STRING_ARRAY_TOKEN };

typedef enum GttPKVFTokenType GttPKVFTokenType;
typedef union GttPKVFTokenValue GttPKVFTokenValue;
typedef struct GttPKVFToken GttPKVFToken;

union GttPKVFTokenValue {
  const char *str;
  GttVector_string *vec;
};
struct GttPKVFToken {
  const char *key;
  GttPKVFTokenValue val;
  GttPKVFTokenType type;
};

#undef GTT_VEC_TYPE
#undef GTT_VEC_NAME
#undef gtt_vec_compare_elements

#define GTT_VEC_TYPE GttPKVFToken
#define GTT_VEC_NAME pkvf_token
#define GTT_VEC_DISABLE_INDEX_OF

#include <getter/types/vector.h>

/**
 * Parses PKVF to the form of token vector.
 *
 * PKVF (Primitive Key-Value Format) is a simple internal data format.
 * It is used while reading the information stored in GetterRelease files.
 * Syntax:
 * \code
 * key@#@value
 * another key@#@another value
 * array@#@element1@,@elemnt2
 * \endcode
 * No quotes, no underscores in keys, only plain strings. New lines indicate new
 * key-value pair. Key is separated from the value by the `@#@` keys
 * sequence. Note that neither key nor value cannot contain that sequence.
 * Value can also be an array of strings - individual strings are divided by
 * `@,@` keys sequence.
 *
 * \param pkvf PKVF string. It must not be a string literal.
 * \param vec Pointer to a pointer to an uninitialized token vector to fill
 * in. \returns True if there was no errors while parsing PKVF.
 */
WINDLL bool gtt_parse_pkvf(const char *pkvf, GttVector_pkvf_token **vec);

HEADER_END

#endif /* TYPES_PKVF_H_ */
