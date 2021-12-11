/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_RELEASE_EXTRACTED_RELEASE_H_
#define INCLUDE_GETTER_RELEASE_EXTRACTED_RELEASE_H_

#include <getter/box/info.h>
#include <getter/release/info.h>
#include <getter/release/release.h>
#include <getter/types/array.h>

GTT_HEADER_BEGIN

/**
 * Full info about the extracted Release (in other words - GttRelease merged
 * with GttReleaseInfo and GttBoxInfo).
 */
typedef struct GttExtractedRelease {
  const char platform[GTT_BUFLEN];  ///< Release's platform (usually OS), e.g.
                                    ///< win32, darwin, linux.

  const char arch[GTT_BUFLEN];  ///< Platform's processor architecture (e.g.
                                ///< x86, x86_64, arm, arm64).

  const char version[GTT_BUFLEN];  ///< Version of the Release (must match
                                   ///< `/[0-9]+\.[0-9]+\.[0-9]+/`).

  const char
      getter[GTT_BUFLEN];  ///< Minimum libgetter version reuired by the Box
                           ///< (must match `/^[0-9]+\.[0-9]+\.[0-9]+$/`).
  GTT_REQUIRED const char script[GTT_BUFLEN];

  GTT_REQUIRED const char name[GTT_BUFLEN];
  GTT_REQUIRED const char full_name[GTT_BUFLEN];
  GTT_REQUIRED const char summary[GTT_BUFLEN];
  const char description[GTT_BUFLEN];

  const char homepage[GTT_BUFLEN];
  const char repository[GTT_BUFLEN];
  GTT_REQUIRED GttCStrArr authors;
  GttCStrArr categories;

  GTT_REQUIRED const char
      license_name[GTT_BUFLEN];  ///< Name of the license (like MIT, GPLv3,
                                 ///< etc.).

  const char license[GTT_BUFLEN];    ///< Path to the license file.
  const char readme[GTT_BUFLEN];     ///< Path to the readme file.
  const char changelog[GTT_BUFLEN];  ///< Path to the changelog file.

  GttCStrArr dependencies;
  GttCStrArr build_dependencies;
  GttCStrArr optional_dependencies;
  GttCStrArr conflicts;
  GttCStrArr replaces;
} GttExtractedRelease;

/**
 * Creates new `GttExtractedRelease` from `GttRelease`, `GttReleaseInfo` and
 * `GttBoxInfo`.
 *
 * \param r `GttRelease` of the Release.
 * \param ri `GttReleaseInfo` of the Release.
 * \param bi `GttBoxInfo` of the Box the Release belongs to.
 * \returns Created GttExtractedRelease.
 * \see GttExtractedRelease
 * \see GttRelease
 * \see GttReleaseInfo
 * \see GttBoxInfo
 */
GTT_ERROR_EMITTER GTT_API GttExtractedRelease *gtt_extracted_release_new(
    GttRelease *r, GttReleaseInfo *ri, GttBoxInfo *bi);

/**
 * Deletes existing GttExtractedRelease.
 *
 * \param self Pointer to GttExtractedRelease to delete.
 * \see GttExtractedRelease
 */
GTT_API void gtt_extracted_release_delete(GttExtractedRelease *self);

GTT_HEADER_END

#endif /* INCLUDE_GETTER_RELEASE_EXTRACTED_RELEASE_H_ */
