# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021 dotandl                               |
# +----------------------------------------------------------+

include("${PROJECT_SOURCE_DIR}/cmake/incstr.cmake")

set(LIBGETTER_SOURCES
  box/info.c
  box/box.c
  release/info.c
  release/extracted_release.c
  release/release.c
  release/version.c
  types/json.c
  types/string.c
  types/array.c
  tools/platform.c
  tools/version.c
  tools/error.c
  tools/tmp.c
  tools/fsmgmt.c
  files/zip/box_info.c
  files/zip/box.c
  files/zip/release_extract.c
  files/zip/release_info.c
  files/zip/package.c
  script/script_runner.c
  db/init.c
)

set(LIBGETTER_HEADERS
  # Headers WITHOUT corresponding source files
  getter.h
  fs/resolve_path.h

  # Headers WITH corresponding source files
  box/info.h
  box/box.h
  release/info.h
  release/extracted_release.h
  release/release.h
  release/version.h
  types/json.h
  types/string.h
  types/array.h
  tools/platform.h
  tools/version.h
  tools/error.h
  tools/tmp.h
  tools/fsmgmt.h
  files/zip/box_info.h
  files/zip/box.h
  files/zip/release_extract.h
  files/zip/release_info.h
  files/zip/package.h
  script/script_runner.h
  db/init.h
)

# Platform-specific source/header files
if(WIN32)
  list(APPEND LIBGETTER_SOURCES
    script/runners/cmd.c
  )

  list(APPEND LIBGETTER_HEADERS
    script/runners/cmd.h
  )
else()
  list(APPEND LIBGETTER_SOURCES
    script/runners/sh.c
  )

  list(APPEND LIBGETTER_HEADERS
    script/runners/sh.h
  )
endif()

# Common dependencies (no matter if building shared or static lib)
set(LIBGETTER_DEPENDENCIES
  json-c
  zip
  pcre2
  sqlite3
)

# All header files are in "<libgetter>/include/getter/" directory, so their
# location need to be prepended with that location
list(TRANSFORM LIBGETTER_HEADERS PREPEND ${PROJECT_SOURCE_DIR}/include/getter/)

# Common header contains some constants used everywhere such as GTT_API,
# GTT_HEADER_BEGIN or GTT_HEADER_END
set(LIBGETTER_COMMON_HEADER_TEMPLATE "${PROJECT_SOURCE_DIR}/common.h.in")
set(LIBGETTER_COMMON_HEADER "${PROJECT_BINARY_DIR}/common.h")
configure_file(
  ${LIBGETTER_COMMON_HEADER_TEMPLATE}
  ${LIBGETTER_COMMON_HEADER}
  @ONLY
)

add_library(getter ${LIBGETTER_SOURCES} ${LIBGETTER_HEADERS})
target_include_directories(getter PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(getter PUBLIC ${LIBGETTER_DEPENDENCIES})

# Force include common header
if(MSVC)
  target_compile_options(getter PUBLIC /FI"${LIBGETTER_COMMON_HEADER}")
else()
  target_compile_options(getter PUBLIC -include "${LIBGETTER_COMMON_HEADER}")
endif()

# Enable GTT_API constant which takes care of exporting symbols in DLLs on Windows
if(WIN32 AND BUILD_SHARED_LIBS)
  target_compile_definitions(getter PUBLIC GTT_DLLBUILD)
endif()

# Decide whether to enable position independent code or not
if(BUILD_SHARED_LIBS)
  set(LIBGETTER_PIC ON)
else()
  set(LIBGETTER_PIC OFF)
endif()

# Set output directory; set C standard; enable -fPIC if needed
set_target_properties(getter PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${LIBGETTER_OUTDIR}
  LIBRARY_OUTPUT_DIRECTORY ${LIBGETTER_OUTDIR}
  RUNTIME_OUTPUT_DIRECTORY ${LIBGETTER_OUTDIR} # For Windows DLLs RUNTIME_... should be used

  C_STANDARD 90 # TODO: convert the project to be C89 compatible
  POSITION_INDEPENDENT_CODE ${LIBGETTER_PIC}
)

# Prepare text files to be included as C strings
incstr("db/sql/init.sql")
