/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_FILES_ZIP_RELEASE_EXTRACT_H_
#define INCLUDE_GETTER_FILES_ZIP_RELEASE_EXTRACT_H_

GTT_HEADER_BEGIN

#include <getter/release/release.h>
#include <zip.h>

/**
 * Extracts the Release of version `version`, platform `platform` and processor
 * architecture `arch` to the temporary directory in order to install that
 * Release.
 *
 * \param zip Pointer to the zip Box object
 * \param release Release to be extracted
 * \param buf Buffer to write the path of the extracted Release to
 * \param bufsize Size of the `buf`
 * \returns The same pointer you pass as a `buf` parameter
 */
GTT_ERROR_EMITTER GTT_API const char *gtt_zip_extract_release(
    zip_t *zip, GttRelease *release, char *buf, size_t bufsize);

GTT_HEADER_END

#endif /* INCLUDE_GETTER_FILES_ZIP_RELEASE_EXTRACT_H_ */
