/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_TYPES_PKVF_H_
#define INCLUDE_GETTER_TYPES_PKVF_H_

#define CVECTOR_LOGARITHMIC_GROWTH

#include <cvector.h>

HEADER_BEGIN

enum GttPKVFTokenType { GTT_PKVF_STRING_TOKEN, GTT_PKVF_STRING_VECTOR_TOKEN };

typedef enum GttPKVFTokenType GttPKVFTokenType;
typedef union GttPKVFTokenValue GttPKVFTokenValue;
typedef struct GttPKVFToken GttPKVFToken;

union GttPKVFTokenValue {
  const char *str;
  cvector_vector_type(char *) vec;
};
struct GttPKVFToken {
  const char *key;
  GttPKVFTokenValue val;
  GttPKVFTokenType type;
};

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
 * \returns Vector with tokens read from PKVF.
 */
GTT_ERROR_EMITTER WINDLL cvector_vector_type(GttPKVFToken)
    gtt_parse_pkvf(const char *pkvf);

/**
 * Frees every key and value in PKVF token vector and then calls
 * gtt_vector_pkvf_token_delete().
 * Call this function instead of calling gtt_vector_pkvf_token_delete().
 *
 * \param vec Token vector to free.
 */
WINDLL void gtt_vector_pkvf_token_free(cvector_vector_type(GttPKVFToken) vec);

HEADER_END

#endif /* INCLUDE_GETTER_TYPES_PKVF_H_ */
