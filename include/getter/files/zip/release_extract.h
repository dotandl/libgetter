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

HEADER_BEGIN

#include <zip.h>

/**
 * Extracts the Release of version `version`, platform `platform` and processor
 * architecture `arch` to the temporary directory in order to install that
 * Release.
 *
 * \param zip Pointer to the zip Box object
 * \param version Version of the extracted Relese
 * \param platform Platform of the extracted Relese
 * \param arch Processor architecture of the extracted Relese
 * \param buf Buffer to write the path of the extracted Release to
 * \param bufsize Size of the `buf`
 * \returns The same pointer you pass as a `buf` parameter
 */
GTT_ERROR_EMITTER WINDLL const char *gtt_zip_extract_release(
    zip_t *zip, const char *version, const char *platform, const char *arch,
    char *buf, size_t bufsize);

HEADER_END

#endif /* INCLUDE_GETTER_FILES_ZIP_RELEASE_EXTRACT_H_ */
