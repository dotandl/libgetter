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

HEADER_END

#endif /* INCLUDE_GETTER_BOX_BOX_H_ */
