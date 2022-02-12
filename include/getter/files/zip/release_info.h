/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021-2022 dotandl                          |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_FILES_ZIP_RELEASE_INFO_H_
#define INCLUDE_GETTER_FILES_ZIP_RELEASE_INFO_H_

GTT_HEADER_BEGIN

#include <getter/release/info.h>
#include <getter/release/release.h>
#include <zip.h>

/**
 * Reads the GetterRelease.json file of `release` from the `zip`.
 *
 * \param zip Zip Box to read the GttReleaseInfo from.
 * \param release Release to retrieve info
 * \returns Representation of GetterRelease.json read from the zip Box.
 * \see GttReleaseInfo
 */
GTT_ERROR_EMITTER GTT_API GttReleaseInfo *gtt_zip_read_release_info(
    zip_t *zip, GttRelease *release);

GTT_HEADER_END

#endif /* INCLUDE_GETTER_FILES_ZIP_RELEASE_INFO_H_ */
