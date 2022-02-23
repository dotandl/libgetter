/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/script/script_runner.h>
#include <getter/types/string.h>
#include <stddef.h>

#ifdef _WIN32
#include <getter/script/runners/cmd.h>
#else
#include <getter/script/runners/sh.h>
#endif

GttScriptRunner *gtt_script_runners[] = {
#ifdef _WIN32
    &cmd_sr,
#else
    &sh_sr,
#endif
    NULL,
};

GttScriptRunner *gtt_script_runner_get(const char *script_file) {
  GttScriptRunner **sr;
  size_t i;

  for (sr = gtt_script_runners; sr != NULL; sr++) {
    for (i = 0; i < (*sr)->n_extensions; i++) {
      if (gtt_str_ends_with(script_file, (*sr)->extensions[i])) {
        return *sr;
      }
    }
  }

  return NULL;
}
