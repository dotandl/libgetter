/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_FILES_ZIP_BOX_INFO_H_
#define INCLUDE_GETTER_FILES_ZIP_BOX_INFO_H_

#include <getter/box/info.h>

HEADER_BEGIN

/**
 * Reads GetterBox.json file withing Box file (in the form of zip file).
 *
 * \param file Path to the zip file.
 * \returns Pointer to GttBoxInfo struct generated from Box file or NULL if an
 * error occurred.
 * \see GttBoxInfo
 */
GTT_ERROR_EMITTER WINDLL GttBoxInfo *gtt_zip_read_box_info(const char *file);

HEADER_END

#endif /* INCLUDE_GETTER_FILES_ZIP_BOX_INFO_H_ */
