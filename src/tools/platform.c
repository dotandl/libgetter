/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/tools/platform.h>
#include <stddef.h>
#include <stdio.h>

static char gtt_platform[GTT_BUFLEN] = {0};
static char gtt_arch[GTT_BUFLEN] = {0};

/*
 * Mocking functions are not exposed in header file. They must be explicitly
 * declared in tests' source files.
 */
GTT_API void gtt_mock_platform(const char *platform);
GTT_API void gtt_mock_arch(const char *arch);

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

const char *gtt_get_platform(void) {
  if (*gtt_platform != 0) return gtt_platform;

#ifdef GTT_PLATFORM
  return GTT_PLATFORM;
#else
  return NULL;
#endif
}

const char *gtt_get_arch(void) {
  if (*gtt_platform != 0) return gtt_arch;

#ifdef GTT_ARCH
  return GTT_ARCH;
#else
  return NULL;
#endif
}

void gtt_mock_platform(const char *platform) {
  if (platform == NULL)
    *gtt_platform = 0;
  else
    snprintf(gtt_platform, GTT_BUFLEN, "%s", platform);
}

void gtt_mock_arch(const char *arch) {
  if (arch == NULL)
    *gtt_arch = 0;
  else
    snprintf(gtt_arch, GTT_BUFLEN, "%s", arch);
}
