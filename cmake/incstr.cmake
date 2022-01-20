# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021-2022 dotandl                          |
# +----------------------------------------------------------+

include_directories("${PROJECT_BINARY_DIR}")

# This function allows to include a text file as a string using #include directive.
#
# CMakeLists.txt:
# include("${PROJECT_SOURCE_DIR}/cmake/incstr.cmake")
# incstr("path/to/file_to_include.txt")
#
# main.c:
# // Quotes are optional; VSCode complains when they aren't present
# const char *file = ""
# #include <incstr/file_to_include.txt>
# ;
function(incstr file)
  # Read file in order to prepare it to include
  file(READ "${file}" content)
  set(out "")

  # Each quotes must be escaped
  string(REPLACE "\"" "\\\"" content "${content}")

  # CMake uses semicolons to separate list's elements so each semicolon must be
  # temporairly replaced
  string(REPLACE ";" "<semicolon>" content "${content}")

  # Split the whole file into lines and put quotes around them
  string(REPLACE "\n" ";" lines "${content}")
  foreach(line ${lines})
    string(APPEND out "\"${line}\\n\"\n")
  endforeach()

  # Restore semicolons
  string(REPLACE "<semicolon>" ";" out "${out}")

  # Get the base filename and save the file
  get_filename_component(filename "${file}" NAME)
  file(WRITE "${PROJECT_BINARY_DIR}/incstr/${filename}" "${out}")
endfunction()
