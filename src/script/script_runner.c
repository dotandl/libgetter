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

#ifndef _WIN32
#include <getter/script/runners/sh.h>
#endif

GttScriptRunner *gtt_script_runners[] = {
#ifndef _WIN32
    &sh_sr,
#endif
    NULL,
};
