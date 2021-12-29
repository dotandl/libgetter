/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_SCRIPT_RUNNERS_CMD_H_
#define INCLUDE_GETTER_SCRIPT_RUNNERS_CMD_H_

#include <getter/script/script_runner.h>

GTT_HEADER_BEGIN

/**
 * Script runner able to run Windows batch files (.cmd, .bat).
 */
GTT_API extern GttScriptRunner cmd_sr;

GTT_HEADER_END

#endif /* INCLUDE_GETTER_SCRIPT_RUNNERS_CMD_H_ */
