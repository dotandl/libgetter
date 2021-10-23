# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021 dotandl                               |
# +----------------------------------------------------------+

set(LIBGETTER_SOURCES
  box/info.c
  box/box.c
  release/info.c
  release/release.c
  release/version.c
  types/pkvf.c
  types/json.c
  tools/platform.c
  tools/version.c
  tools/error.c
  tools/tmp.c
  files/zip/box_info.c
  files/zip/box.c
)

set(LIBGETTER_HEADERS
  # Headers WITHOUT corresponding source files
  getter.h
  common.h
  attributes.h
  types/array.h

  # Headers WITH corresponding source files
  box/info.h
  box/box.h
  release/info.h
  release/release.h
  release/version.h
  types/pkvf.h
  types/json.h
  tools/platform.h
  tools/version.h
  tools/error.h
  tools/tmp.h
  files/zip/box_info.h
  files/zip/box.h
)

# Common dependencies (no matter if building shared or static lib)
set(LIBGETTER_DEPENDENCIES
  zip
  pcre2
  jsmn
  c-vector
)

# All header files are in "<libgetter>/include/getter/" directory, so their
# location need to be prepended with that location
list(TRANSFORM LIBGETTER_HEADERS PREPEND ${PROJECT_SOURCE_DIR}/include/getter/)

# Common header contains some constants used everywhere such as WINDLL, HEADER_BEGIN or HEADER_END
set(LIBGETTER_COMMON_HEADER ${PROJECT_SOURCE_DIR}/include/getter/common.h)

add_library(getter ${LIBGETTER_SOURCES} ${LIBGETTER_HEADERS})
target_include_directories(getter PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(getter PUBLIC ${LIBGETTER_DEPENDENCIES})

target_compile_definitions(getter
  PUBLIC GTT_VERSION="${LIBGETTER_VERSION}"
  PUBLIC GTT_VERSION_SHORT="${LIBGETTER_VERSION_SHORT}"
  PUBLIC GTT_VERSION_MAJOR=${LIBGETTER_VERSION_MAJOR}
  PUBLIC GTT_VERSION_MINOR=${LIBGETTER_VERSION_MINOR}
  PUBLIC GTT_VERSION_PATCH=${LIBGETTER_VERSION_PATCH}
)

# Force include common header
if(MSVC)
  target_compile_options(getter PUBLIC /FI"${LIBGETTER_COMMON_HEADER}")
else()
  target_compile_options(getter PUBLIC -include "${LIBGETTER_COMMON_HEADER}")
endif()

# Enable WINDLL constant which takes care of exporting symbols in DLLs on Windows
if(WIN32 AND BUILD_SHARED_LIBS)
  target_compile_definitions(getter PUBLIC WINDLLBUILD)
endif()

# Decide whether to enable position independent code or not
if(BUILD_SHARED_LIBS)
  set(LIBGETTER_PIC ON)
else()
  set(LIBGETTER_PIC OFF)
endif()

# Set C standard; enable -fPIC if needed
set_target_properties(getter PROPERTIES
  C_STANDARD 11 # TODO: convert the project to be C89 compatible
  POSITION_INDEPENDENT_CODE ${LIBGETTER_PIC}
)
