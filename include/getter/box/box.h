/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_BOX_BOX_H_
#define INCLUDE_GETTER_BOX_BOX_H_

#include <getter/box/info.h>
#include <getter/release/release.h>
#include <getter/types/vectors/release.h>

HEADER_BEGIN

/** Basic representation of the Box. */
struct GttBox {
  GttBoxInfo *info;
  GttVector_release *releases;
};

typedef struct GttBox GttBox;

/**
 * Creates new GttBox.
 *
 * \param info Info about the Box (the object IS NOT copied so make sure to not
 * delete the GttBoxInfo after creating GttBox).
 * \param releases All the Releases available in the Box (again - Vector is not
 * copied so do not delete it).
 * \returns Created GttBox.
 * \see GttBox
 */
WINDLL GttBox *gtt_box_new(GttBoxInfo *info, GttVector_release *releases);

/**
 * Deletes existing GttBox.
 *
 * \param self Pointer to GttBox to delete.
 * \see GttBox
 */
WINDLL void gtt_box_delete(GttBox *self);

/**
 * Returns selected version of the Release for a given platform and
 * architecture.
 *
 * \param self Box to search for the Release in.
 * \param version Version of the Release (or NULL for the latest one).
 * \param platform Target platform of the Release (or NULL for the host one).
 * \param arch Target processor architecture of the Release (or NULL for the
 * host one).
 * \returns Selected version of the Release for selected platform and
 * architecture.
 * \see GttBox
 */
WINDLL GttRelease *gtt_box_get_release(GttBox *self, const char *version,
                                       const char *platform, const char *arch);

/**
 * Returns the latest Release for host platform and architecture.
 *
 * \param self Box to search for the Release in.
 * \returns The latest Release for host platform and architecture.
 * \see GttBox
 */
inline GttRelease *gtt_box_get_appropriate_release(GttBox *self) {
  return gtt_box_get_release(self, NULL, NULL, NULL);
}

HEADER_END

#endif /* INCLUDE_GETTER_BOX_BOX_H_ */
