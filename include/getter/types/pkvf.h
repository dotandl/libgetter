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
#include <getter/types/vec.h>
#include <stdbool.h>

HEADER_BEGIN

/**
 * Parses PKVF to the form of key-value vector.
 *
 * PKVF (Primitive Key-Value Format) is a simple internal data format.
 * It is used while reading the information stored in GetterRelease files.
 * Syntax:
 * \code
 * key@#@value
 * another key@#@another value
 * \endcode
 * No quotes, no underscores in keys, only plain strings. New lines indicate new
 * key-value pair. Key is separated from the value by the `@#@` keys
 * sequence. Note that neither key nor value cannot contain that sequence.
 *
 * \param pkvf PKVF string. It must not be a string literal.
 * \param vec Pointer to uninitialized key-value vector to fill in.
 * \returns True if there was no errors while parsing PKVF.
 */
WINDLL bool gtt_parse_pkvf(const char *pkvf, vec_keyval_t *vec);

HEADER_END

#endif /* TYPES_PKVF_H_ */
