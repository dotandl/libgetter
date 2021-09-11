/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_TOOLS_VERSION_H_
#define INCLUDE_GETTER_TOOLS_VERSION_H_

HEADER_BEGIN

#include <stdbool.h>

/**
 * Checks whether _current version_ is newer than _version_. Both _current
 * version_ and _version_ must be in the form of MAJOR.MINOR.PATCH.
 *
 * \param c_major _MAJOR_ part of _version_.
 * \param c_minor _MINOR_ part of _version_.
 * \param c_patch _PATCH_ part of _version_.
 * \param major _MAJOR_ part of _current version_.
 * \param minor _MINOR_ part of _current version_.
 * \param patch _PATCH_ part of _current version_.
 * \returns whether _current version_ is newer than _version_ or not.
 */
WINDLL bool gtt_is_newer(unsigned int c_major, unsigned int c_minor,
                         unsigned int c_patch, unsigned int major,
                         unsigned int minor, unsigned int patch);

HEADER_END

#endif /* INCLUDE_GETTER_TOOLS_VERSION_H_ */
