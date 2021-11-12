/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_TOOLS_TOUCH_H_
#define INCLUDE_GETTER_TOOLS_TOUCH_H_

#include <stddef.h>

GTT_HEADER_BEGIN

/**
 * Creates new file in the _path_ with _contents_ of _size_.
 *
 * \param path The path where the file should be created.
 * \param contents The contents of the file.
 * \param size The size of the file.
 */
GTT_API void gtt_new_file_mkdir_parents(const char *path, void *contents,
                                        size_t size);

GTT_HEADER_END

#endif /* INCLUDE_GETTER_TOOLS_TOUCH_H_ */
