/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef COMMON_H_
#define COMMON_H_

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
#define WINDLL __declspec(dllimport)
#endif
#else
#define WINDLL
#endif

#endif /* COMMON_H_ */
