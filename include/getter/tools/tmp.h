/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_TOOLS_TMP_H_
#define INCLUDE_GETTER_TOOLS_TMP_H_

HEADER_BEGIN

#include <stddef.h>

/**
 * Creates a temporary directory
 *
 * \param buf Buffer to write the directory path to
 * \param bufsize Size of the `buf` buffer
 * \returns The same pointer as you pass as a `buf` pointer
 */
WINDLL char *gtt_mktmpdir(char *buf, size_t bufsize);

HEADER_END

#endif /* INCLUDE_GETTER_TOOLS_TMP_H_ */
