/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_BOX_INFO_H_
#define INCLUDE_GETTER_BOX_INFO_H_

#define CVECTOR_LOGARITHMIC_GROWTH

#include <cvector.h>

GTT_HEADER_BEGIN

/** Representation of GetterBox.json file. */
typedef struct GttBoxInfo {
  const char
      getter[GTT_BUFLEN];  ///< Minimum libgetter version reuired by the Box
                           ///< (must match `/^[0-9]+\.[0-9]+\.[0-9]+$/`).

  GTT_REQUIRED const char name[GTT_BUFLEN];
  GTT_REQUIRED const char full_name[GTT_BUFLEN];
  GTT_REQUIRED const char summary[GTT_BUFLEN];
  const char description[GTT_BUFLEN];

  const char homepage[GTT_BUFLEN];
  const char repository[GTT_BUFLEN];
  GTT_REQUIRED cvector_vector_type(char *) authors;
  cvector_vector_type(char *) categories;

  GTT_REQUIRED const char
      license_name[GTT_BUFLEN];      ///< Name of the license (like MIT, GPLv3,
                                     ///< etc.).
  const char license[GTT_BUFLEN];    ///< Path to the license file.
  const char readme[GTT_BUFLEN];     ///< Path to the readme file.
  const char changelog[GTT_BUFLEN];  ///< Path to the changelog file.

  cvector_vector_type(char *) dependencies;
  cvector_vector_type(char *) build_dependencies;
  cvector_vector_type(char *) optional_dependencies;
  cvector_vector_type(char *) conflicts;
  cvector_vector_type(char *) replaces;
} GttBoxInfo;

/**
 * Creates new GttBoxInfo from the contents of GetterBox.json file.
 *
 * \param json The contents of GetterBox.json file.
 * \returns Created GttBoxInfo.
 * \see GttBoxInfo
 */
GTT_ERROR_EMITTER GTT_API GttBoxInfo *gtt_box_info_new_from_json(
    const char *json);

/**
 * Deletes existing GttBoxInfo.
 *
 * \param self Pointer to GttBoxInfo to delete.
 * \see GttBoxInfo
 */
GTT_API void gtt_box_info_delete(GttBoxInfo *self);

GTT_HEADER_END

#endif /* INCLUDE_GETTER_BOX_INFO_H_ */
