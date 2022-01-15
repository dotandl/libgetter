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
#include <getter/types/array.h>

GTT_HEADER_BEGIN

/** Basic representation of the Box. */
typedef struct GttBox {
  GttBoxInfo *info;
  GttPtrArr releases;  ///< Array of `GttRelease *`
} GttBox;

/**
 * Creates new GttBox.
 *
 * \param info Info about the Box (the object IS NOT copied so make sure to not
 * delete the GttBoxInfo after creating GttBox).
 * \param releases All the Releases available in the Box (again - array is not
 * copied so do not delete it).
 * \returns Created GttBox.
 * \see GttBox
 */
GTT_API GttBox *gtt_box_new(GttBoxInfo *info, GttPtrArr releases);

/**
 * Deletes existing GttBox.
 *
 * \param self Pointer to GttBox to delete.
 * \see GttBox
 */
GTT_API void gtt_box_delete(GttBox *self);

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
GTT_ERROR_EMITTER GTT_API GttRelease *gtt_box_get_release(GttBox *self,
                                                          const char *version,
                                                          const char *platform,
                                                          const char *arch);

/**
 * Returns the latest Release for host platform and architecture.
 *
 * \param self Box to search for the Release in.
 * \returns The latest Release for host platform and architecture.
 * \see GttBox
 */
#define gtt_box_get_appropriate_release(self) \
  gtt_box_get_release((self), NULL, NULL, NULL)

GTT_HEADER_END

#endif /* INCLUDE_GETTER_BOX_BOX_H_ */
