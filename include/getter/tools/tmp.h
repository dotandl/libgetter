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

GTT_HEADER_BEGIN

#include <stddef.h>

/**
 * Creates a temporary directory.
 *
 * \param buf Buffer to write the directory path to.
 * \param bufsize Size of the `buf` buffer.
 * \returns The same pointer as you pass as a `buf` pointer.
 */
GTT_API char *gtt_mktmpdir(char *buf, size_t bufsize);

/**
 * Recursively removes a temporary directory.
 *
 * \param path Path to the temporary directory.
 */
GTT_API void gtt_rmtmpdir(const char *path);

GTT_HEADER_END

#endif /* INCLUDE_GETTER_TOOLS_TMP_H_ */
