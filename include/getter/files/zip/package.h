/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021-2022 dotandl                          |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_FILES_ZIP_PACKAGE_H_
#define INCLUDE_GETTER_FILES_ZIP_PACKAGE_H_

#include <zip.h>

GTT_HEADER_BEGIN

GTT_API GTT_ERROR_EMITTER void gtt_zip_package_install(zip_t *zip);

GTT_HEADER_END

#endif /* INCLUDE_GETTER_FILES_ZIP_PACKAGE_H_ */
