/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef TOOLS_PLATFORM_H_
#define TOOLS_PLATFORM_H_

#include <getter/decl.h>

HEADER_BEGIN

#pragma region GTT_PLATFORM

/* Windows */
#if defined(_WIN32)
#define GTT_PLATFORM "win32"

#elif defined(__APPLE__) && defined(__MACH__)
#include <TargetConditionals.h>
/* macOS */
#if TARGET_OS_MAC == 1
#define GTT_PLATFORM "darwin"
#endif

/* Linux-based */
#elif defined(__linux__) && !defined(__ANDROID__)
#define GTT_PLATFORM "linux"

/* FreeBSD */
#elif defined(__FreeBSD__)
#define GTT_PLATFORM "freebsd"
#endif

#pragma endregion GTT_PLATFORM

#pragma region GTT_ARCH

/* x86_64 (aka x64, amd64) */
#if defined(__amd64__) || defined(_M_AMD64)
#define GTT_ARCH "x86_64"

/* x86 (aka i386) */
#elif defined(i386) || defined(_M_IX86)
#define GTT_ARCH "x86"

/* arm64 */
#elif defined(__aarch64__) || defined(_M_ARM64)
#define GTT_ARCH "arm64"

/* arm */
#elif defined(__arm__) || defined(_M_ARM)
#define GTT_ARCH "arm"
#endif

#pragma endregion GTT_ARCH

HEADER_END

#endif /* TOOLS_PLATFORM_H_ */
