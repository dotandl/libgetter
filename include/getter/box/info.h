/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef BOX_INFO_H_
#define BOX_INFO_H_

#include <string.h>

#define GTT_VEC_TYPE char *
#define GTT_VEC_NAME string
#define gtt_vec_compare_elements(el1, el2) strcmp(el1, el2) == 0

#include <getter/decl.h>
#include <getter/types/vector.h>

HEADER_BEGIN

/** Representation of GetterBox.json file. */
struct GttBoxInfo {
  const char *name;
  const char *full_name;
  const char *summary;
  const char *description;

  const char *homepage;
  const char *repository;
  GttVector_string *authors;
  GttVector_string *categories;

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

typedef struct GttBoxInfo GttBoxInfo;

/**
 * Creates new GttBoxInfo from the contents of GetterBox.json file.
 *
 * \param json The contents of GetterBox.json file.
 * \returns Created GttBoxInfo.
 * \see GttBoxInfo
 */
WINDLL GttBoxInfo *gtt_box_info_new_from_json(const char *json);

/**
 * Deletes existing GttBoxInfo.
 *
 * \param self Pointer to GttBoxInfo to delete.
 * \see GttBoxInfo
 */
WINDLL void gtt_box_info_delete(GttBoxInfo *self);

HEADER_END

#endif /* BOX_INFO_H_ */
