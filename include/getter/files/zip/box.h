/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_FILES_ZIP_BOX_H_
#define INCLUDE_GETTER_FILES_ZIP_BOX_H_

#include <getter/box/box.h>

HEADER_BEGIN

/**
 * Generates Box object basing on the Box file in the form of zip file.
 *
 * \param file Path to the zip file.
 * \returns Pointer to GttBox struct generated from the Box file or NULL if an
 * error occurred.
 * \see GttBox
 */
GTT_ERROR_EMITTER WINDLL GttBox *gtt_zip_read_box(const char *file);

HEADER_END

#endif /* INCLUDE_GETTER_FILES_ZIP_BOX_H_ */