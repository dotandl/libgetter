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

#include <getter/types/pkvf.h>

HEADER_BEGIN

/** Representation of the info section of GetterRelease file. */
struct GttReleaseInfo {
  GTT_REQUIRED const char *script;

  const char *repository;

  const char *license_name;  ///< Name of the license (like MIT, GPLv3, etc.).
  const char *license;       ///< Path to the license file.
  const char *readme;        ///< Path to the readme file.
  const char *changelog;     ///< Path to the changelog file.

  cvector_vector_type(char *) dependencies;
  cvector_vector_type(char *) build_dependencies;
  cvector_vector_type(char *) optional_dependencies;
  cvector_vector_type(char *) conflicts;
  cvector_vector_type(char *) replaces;
};

typedef struct GttReleaseInfo GttReleaseInfo;

/**
 * Creates new GttReleaseInfo from the PKVF generated from the
 * GetterRelease file.
 *
 * \param pkvf PKVF generated from the contents of the GetterRelease file.
 * \returns Created GttReleaseInfo.
 * \see GttReleaseInfo
 */
GTT_ERROR_EMITTER WINDLL GttReleaseInfo *gtt_release_info_new_from_pkvf(
    const char *pkvf);

/**
 * Creates new GttReleaseInfo from the PKVF generated from the
 * GetterRelease.json file.
 *
 * \param json The contents of GetterRelease.json file.
 * \returns Created GttReleaseInfo.
 * \see GttReleaseInfo
 */
GTT_ERROR_EMITTER WINDLL GttReleaseInfo *gtt_release_info_new_from_json(
    const char *json);

/**
 * Deletes existing GttReleaseInfo.
 *
 * \param self Pointer to GttReleaseInfo to delete.
 * \see GttReleaseInfo
 */
WINDLL void gtt_release_info_delete(GttReleaseInfo *self);

HEADER_END

#endif /* INCLUDE_GETTER_RELEASE_INFO_H_ */
