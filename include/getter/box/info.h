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

#include <getter/types/vectors/string.h>

HEADER_BEGIN

/** Representation of GetterBox.json file. */
struct GttBoxInfo {
  const char *getter;  ///< Minimum libgetter version reuired by the Box (must
                       ///< match `/^[0-9]+\.[0-9]+\.[0-9]+$/`).

  GTT_REQUIRED const char *name;
  GTT_REQUIRED const char *full_name;
  GTT_REQUIRED const char *summary;
  const char *description;

  const char *homepage;
  const char *repository;
  GTT_REQUIRED GttVector_string *authors;
  GttVector_string *categories;

  GTT_REQUIRED const char
      *license_name;      ///< Name of the license (like MIT, GPLv3, etc.).
  const char *license;    ///< Path to the license file.
  const char *readme;     ///< Path to the readme file.
  const char *changelog;  ///< Path to the changelog file.

  GttVector_string *dependencies;
  GttVector_string *build_dependencies;
  GttVector_string *optional_dependencies;
  GttVector_string *conflicts;
  GttVector_string *replaces;
};

typedef struct GttBoxInfo GttBoxInfo;

/**
 * Creates new GttBoxInfo from the contents of GetterBox.json file.
 *
 * \param json The contents of GetterBox.json file.
 * \returns Created GttBoxInfo.
 * \see GttBoxInfo
 */
GTT_ERROR_EMITTER WINDLL GttBoxInfo *gtt_box_info_new_from_json(
    const char *json);

/**
 * Deletes existing GttBoxInfo.
 *
 * \param self Pointer to GttBoxInfo to delete.
 * \see GttBoxInfo
 */
WINDLL void gtt_box_info_delete(GttBoxInfo *self);

HEADER_END

#endif /* INCLUDE_GETTER_BOX_INFO_H_ */
