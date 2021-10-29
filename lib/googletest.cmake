# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021 dotandl                               |
# +----------------------------------------------------------+

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON)

add_subdirectory(googletest)

# For Windows: gtest's DLLs have to be in the same directory as text executable is
set_property(
  TARGET gtest gtest_main
  PROPERTY RUNTIME_OUTPUT_DIRECTORY ${LIBGETTER_OUTDIR}
)
