/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef RELEASE_INFO_H_
#define RELEASE_INFO_H_

#include <getter/types/pkvf.h>

HEADER_BEGIN

/** Representation of the info section of GetterRelease file. */
struct GttReleaseInfo {
  const char *repository;

  const char *license_name;  ///< Name of the license (like MIT, GPLv3, etc.).
  const char *license;       ///< Path to the license file.
  const char *readme;        ///< Path to the readme file.
  const char *changelog;     ///< Path to the changelog file.

  GttVector_string *dependencies;
  GttVector_string *build_dependencies;
  GttVector_string *optional_dependencies;
  GttVector_string *conflicts;
  GttVector_string *replaces;
};

typedef struct GttReleaseInfo GttReleaseInfo;

/**
 * Creates new GttReleaseInfo from the PKVF generated from the GetterRelease
 * file.
 *
 * \param pkvf PKVF generated from the contents of the GetterRelease file.
 * \returns Created GttReleaseInfo.
 * \see GttReleaseInfo
 */
WINDLL GttReleaseInfo *gtt_release_info_new_from_pkvf(const char *pkvf);

/**
 * Deletes existing GttReleaseInfo.
 *
 * \param self Pointer to GttReleaseInfo to delete.
 * \see GttReleaseInfo
 */
WINDLL void gtt_release_info_delete(GttReleaseInfo *self);

HEADER_END

#endif /* RELEASE_INFO_H_ */
