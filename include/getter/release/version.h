/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_RELEASE_VERSION_H_
#define INCLUDE_GETTER_RELEASE_VERSION_H_

#include <getter/release/release.h>
#include <getter/types/array.h>

GTT_HEADER_BEGIN

/**
 * Gets the latest Release from the array of Releases.
 *
 * Loops for each Release in the array, searches for MAJOR.MINOR.PATCH string
 * in Release's version using /[0-9]+\.[0-9]+\.[0-9]+/ regexp, compares each
 * number of the version and returns the latest Release.
 *
 * \param releases Array of Releases in which to search for the latest Release.
 * \returns The latest Release.
 */
GTT_ERROR_EMITTER GTT_API GttRelease *gtt_get_latest_release_version(
    GttPtrArr releases);

GTT_HEADER_END

#endif /* INCLUDE_GETTER_RELEASE_VERSION_H_ */
