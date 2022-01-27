/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021-2022 dotandl                          |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_FS_RESOLVE_PATH_H_
#define INCLUDE_GETTER_FS_RESOLVE_PATH_H_

GTT_HEADER_BEGIN

/* Windows */
#if defined(_WIN32)
#define GTT_DATABASE_FILE_PATH "C:\\getter\\getter.db"
#define GTT_EXECUTABLE_FILE_PATH "C:\\getter\\getter.exe"

#elif defined(__APPLE__) && defined(__MACH__)
#include <TargetConditionals.h>
/* macOS */
#if TARGET_OS_MAC == 1
#define GTT_DATABASE_FILE_PATH "/Library/getter/getter.db"
#define GTT_EXECUTABLE_FILE_PATH "/usr/local/bin/getter"
#endif

/* Linux-based */
#elif defined(__linux__) && !defined(__ANDROID__)
#define GTT_DATABASE_FILE_PATH "/var/lib/getter/getter.db"
#define GTT_EXECUTABLE_FILE_PATH "/usr/bin/getter"

/* FreeBSD */
#elif defined(__FreeBSD__)
#define GTT_DATABASE_FILE_PATH "/usr/local/var/lib/getter/getter.db"
#define GTT_EXECUTABLE_FILE_PATH "/usr/local/bin/getter"
#endif

// TODO: delete GTT_EXECUTABLE_FILE_PATHs

GTT_HEADER_END

#endif /* INCLUDE_GETTER_FS_RESOLVE_PATH_H_ */
