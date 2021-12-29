/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/script/script_runner.h>
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
