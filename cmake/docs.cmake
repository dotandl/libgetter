# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021 dotandl                               |
# +----------------------------------------------------------+

find_package(Doxygen)

if(DOXYGEN_FOUND)
  set(LIBGETTER_DOXYFILE_TEMPLATE "${PROJECT_SOURCE_DIR}/Doxyfile.in")
  set(LIBGETTER_DOXYFILE "${PROJECT_BINARY_DIR}/Doxyfile")

  configure_file(${LIBGETTER_DOXYFILE_TEMPLATE} ${LIBGETTER_DOXYFILE} @ONLY)

  add_custom_target(docs
    COMMAND ${DOXYGEN_EXECUTABLE} ${LIBGETTER_DOXYFILE}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Generating documentation..."
  )
else()
  message(WARNING "Doxygen not found. Could not generate documentation.")
endif()
