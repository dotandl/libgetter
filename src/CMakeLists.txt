# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021 dotandl                               |
# +----------------------------------------------------------+

set(SOURCE_FILES
  core.c
)

set(HEADER_FILES
  getter.h
  decl.h

  core.h
)

list(TRANSFORM HEADER_FILES PREPEND ${PROJECT_SOURCE_DIR}/include/getter/)

add_library(libgetter_object OBJECT ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(libgetter_object PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(libgetter SHARED)
add_library(libgetter_static STATIC)

target_link_libraries(libgetter PUBLIC libgetter_object)
target_link_libraries(libgetter_static PUBLIC libgetter_object)

if(WIN32)
  target_compile_definitions(libgetter PRIVATE WINDLLBUILD)
endif()
