/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_RELEASE_INFO_H_
#define INCLUDE_GETTER_RELEASE_INFO_H_

#include <getter/types/array.h>

GTT_HEADER_BEGIN

/** Representation of the info section of GetterRelease file. */
typedef struct GttReleaseInfo {
  GTT_REQUIRED const char script[GTT_BUFLEN];

  const char repository[GTT_BUFLEN];

  const char license_name[GTT_BUFLEN];  ///< Name of the license (like MIT,
                                        ///< GPLv3, etc.).
  const char license[GTT_BUFLEN];       ///< Path to the license file.
  const char readme[GTT_BUFLEN];        ///< Path to the readme file.
  const char changelog[GTT_BUFLEN];     ///< Path to the changelog file.

  GttCStrArr dependencies;
  GttCStrArr build_dependencies;
  GttCStrArr optional_dependencies;
  GttCStrArr conflicts;
  GttCStrArr replaces;
} GttReleaseInfo;

/**
 * Creates new GttReleaseInfo from the PKVF generated from the
 * GetterRelease.json file.
 *
 * \param json The contents of GetterRelease.json file.
 * \returns Created GttReleaseInfo.
 * \see GttReleaseInfo
 */
GTT_ERROR_EMITTER GTT_API GttReleaseInfo *gtt_release_info_new_from_json(
    const char *json);

/**
 * Deletes existing GttReleaseInfo.
 *
 * \param self Pointer to GttReleaseInfo to delete.
 * \see GttReleaseInfo
 */
GTT_API void gtt_release_info_delete(GttReleaseInfo *self);

GTT_HEADER_END

#endif /* INCLUDE_GETTER_RELEASE_INFO_H_ */
