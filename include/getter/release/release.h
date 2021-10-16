/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_RELEASE_RELEASE_H_
#define INCLUDE_GETTER_RELEASE_RELEASE_H_

#include <getter/release/info.h>

HEADER_BEGIN

/** Basic representation of the Release. */
struct GttRelease {
  const char *platform;  ///< Release's platform (usually OS), e.g. win32,
                         ///< darwin, linux.

  const char *arch;  ///< Platform's processor architecture (e.g. x86, x86_64,
                     ///< arm, arm64).

  const char *version;  ///< Version of the Release (must match
                        ///< `/[0-9]+\.[0-9]+\.[0-9]+/`).
};

typedef struct GttRelease GttRelease;

/**
 * Creates new GttRelease.
 *
 * \param platform Release's platform.
 * \param arch Platform's processor architecture.
 * \param version Version of the release.
 * \returns Created GttRelease.
 * \see GttRelease
 */
GTT_ERROR_EMITTER WINDLL GttRelease *gtt_release_new(const char *platform,
                                                     const char *arch,
                                                     const char *version);

/**
 * Deletes existing GttRelease.
 *
 * \param self Pointer to GttRelease to delete.
 * \see GttRelease
 */
WINDLL void gtt_release_delete(GttRelease *self);

HEADER_END

#endif /* INCLUDE_GETTER_RELEASE_RELEASE_H_ */