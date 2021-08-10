/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef INFO_H_
#define INFO_H_

#include <getter/decl.h>
#include <vec.h>

HEADER_BEGIN

/** Representation of GetterBox.json file. */
struct GttBoxInfo {
  const char *name;
  const char *full_name;
  const char *summary;
  const char *description;

  const char *homepage;
  const char *repository;
  vec_str_t *authors;
  vec_str_t *categories;

  const char *license_name;  ///< Name of the license (like MIT, GPLv3, etc.).
  const char *license;       ///< Path to the license file.
  const char *readme;        ///< Path to the readme file.
  const char *changelog;     ///< Path to the changelog file.

  vec_str_t *dependencies;
  vec_str_t *build_dependencies;
  vec_str_t *optional_dependencies;
  vec_str_t *conflicts;
  vec_str_t *replaces;
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

#endif /* INFO_H_ */
