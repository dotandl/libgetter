/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifdef __cplusplus
#define HEADER_BEGIN extern "C" {
#define HEADER_END }
#else
#define HEADER_BEGIN
#define HEADER_END
#endif

#ifdef _WIN32
#ifdef WINDLLBUILD
#define WINDLL __declspec(dllexport)
#else
#define WINDLL __declsped(dllimport)
#endif
#else
#define WINDLL
#endif
