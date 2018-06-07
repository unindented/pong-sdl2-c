find_package(Check REQUIRED)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../src"
                    ${CHECK_INCLUDE_DIR})

add_executable(test_utils test_utils.c)
target_compile_options(test_utils PRIVATE -Wall -Wextra -Wno-format-zero-length)
target_link_libraries(test_utils utils ${CHECK_LIBRARY})

add_executable(test_systems test_systems.c)
target_compile_options(test_systems PRIVATE -Wall -Wextra -Wno-format-zero-length)
target_link_libraries(test_systems game ${CHECK_LIBRARY})

add_custom_target(test_all ALL DEPENDS test_utils test_systems)

add_custom_command(TARGET test_all POST_BUILD
                   COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                   COMMENT "Run tests")
