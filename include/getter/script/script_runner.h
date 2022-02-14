/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_SCRIPT_SCRIPT_RUNNER_H_
#define INCLUDE_GETTER_SCRIPT_SCRIPT_RUNNER_H_

GTT_HEADER_BEGIN

/**
 * Representation of script runner.
 *
 * Script runner is an object that is able to run the install/uninstall/upgrade
 * script of the Release. The name of the script is usually
 * `GetterScript.<ext>`, where <ext> determines the script runner that should be
 * used to run that script.
 */
typedef struct GttScriptRunner {
  const char **extensions;  ///< Extensions that are compatible with the script
                            ///< runner (array of strings; each of string should
                            ///< start with ".").
  unsigned short n_extensions;  ///< Number of strings `extensions` contains.

  int (*prepare)(const char *script, const char *cwd);
  int (*build)(const char *script, const char *cwd);
  int (*install)(const char *script, const char *cwd);
  int (*upgrade)(const char *script, const char *cwd);
  int (*uninstall)(const char *script, const char *cwd);
  int (*clean)(const char *script, const char *cwd);
} GttScriptRunner;

/**
 * List of script runners currently available for a given platform (having NULL
 * as the last element).
 */
GTT_API extern GttScriptRunner *gtt_script_runners[];

/**
 * Gets an appriopriate script runner depending on script file's extension.
 *
 * \param script_file Name of the script file for which the script runner should
 * be get.
 * \returns The script runner to be used with the script or NULL if no
 * script runner was found.
 * \see GttScriptRunner
 */
GTT_API GttScriptRunner *gtt_script_runner_get(const char *script_file);

GTT_HEADER_END

#endif /* INCLUDE_GETTER_SCRIPT_SCRIPT_RUNNER_H_ */
