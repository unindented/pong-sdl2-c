find_path(CHECK_INCLUDE_DIR check.h)
find_library(CHECK_LIBRARY NAMES check)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(CHECK
                                  REQUIRED_VARS CHECK_LIBRARY CHECK_INCLUDE_DIR)
