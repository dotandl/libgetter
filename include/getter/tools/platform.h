/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_TOOLS_PLATFORM_H_
#define INCLUDE_GETTER_TOOLS_PLATFORM_H_

HEADER_BEGIN

/**
 * Gets system platform.
 *
 * \returns System platform (e.g. win32, linux).
 */
const char *gtt_get_platform(void);

/**
 * Gets system's processor architecture.
 *
 * \returns System's processor architecture (e.g. x86, arm64).
 */
const char *gtt_get_arch(void);

HEADER_END

#endif /* INCLUDE_GETTER_TOOLS_PLATFORM_H_ */
