# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021 dotandl                               |
# +----------------------------------------------------------+

set(SOURCE_FILES
  box/info.c
  box/box.c
  release/info.c
  release/release.c
  release/version.c
  types/pkvf.c
)

set(HEADER_FILES
  # Headers WITHOUT corresponding source files
  getter.h
  decl.h
  types/array.h
  types/vector.h
  types/vectors/string.h
  types/vectors/release.h
  tools/platform.h

  # Headers WITH corresponding source files
  box/info.h
  box/box.h
  release/info.h
  release/release.h
  release/version.h
  types/pkvf.h
)

list(TRANSFORM HEADER_FILES PREPEND ${PROJECT_SOURCE_DIR}/include/getter/)

add_library(libgetter_object OBJECT ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(libgetter_object PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(libgetter_object PUBLIC jsmn pcre2-8-static)

add_library(libgetter SHARED)
add_library(libgetter_static STATIC)

target_link_libraries(libgetter PUBLIC libgetter_object)
target_link_libraries(libgetter_static PUBLIC libgetter_object)

set_target_properties(libgetter libgetter_static PROPERTIES OUTPUT_NAME getter)

if(WIN32)
  target_compile_definitions(libgetter PRIVATE WINDLLBUILD)
endif()
