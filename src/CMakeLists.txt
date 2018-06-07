find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${SDL2_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR}
                    ${SDL2_MIXER_INCLUDE_DIR})

# Utils lib

add_library(utils STATIC
            utils/settings.h
            utils/math.h utils/math.c)

target_compile_options(utils PRIVATE -Wall -Wextra)

# Game lib

add_library(game STATIC
            components/component.h
            components/collision.h
            components/controller.h
            components/geometry.h
            components/rigid_body.h
            entities/ball.h entities/ball.c
            entities/paddle.h entities/paddle.c
            entities/wall.h entities/wall.c
            entities/world.h entities/world.c
            systems/keyboard.h systems/keyboard.c
            systems/physics.h systems/physics.c
            systems/rendering.h systems/rendering.c)

target_compile_options(game PRIVATE -Wall -Wextra)
target_link_libraries(game
                      ${SDL2_LIBRARY}
                      ${SDL2_TTF_LIBRARY}
                      ${SDL2_MIXER_LIBRARY})

# Executable

add_executable(${Pong_NAME}
               ${Pong_CONFIG}
               main.c
               ${Pong_MACOSX_APP_ICON}
               ${Pong_WIN_APP_INFO})

if(APPLE)

  set_target_properties(${Pong_NAME} PROPERTIES
                        MACOSX_BUNDLE TRUE
                        MACOSX_BUNDLE_INFO_PLIST ${Pong_MACOSX_BUNDLE_INFO_IN})
  set_source_files_properties(${Pong_MACOSX_APP_ICON} PROPERTIES
                              MACOSX_PACKAGE_LOCATION Resources)

endif()

target_compile_options(${Pong_NAME} PRIVATE -Wall -Wextra)
target_link_libraries(${Pong_NAME}
                      utils
                      game
                      ${SDL2_LIBRARY}
                      ${SDL2_TTF_LIBRARY}
                      ${SDL2_MIXER_LIBRARY})


# Installation

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})

if(APPLE)

  install(CODE "
    include(BundleUtilities)

    macro(fixup_bundle_item resolved_embedded_item exepath dirs)
      message(\"Making writable: \${resolved_embedded_item}\")
      execute_process(COMMAND chmod +w \"\${resolved_embedded_item}\")
      _fixup_bundle_item(\"\${resolved_embedded_item}\" \"\${exepath}\" \"\${dirs}\")
    endmacro()

    fixup_bundle(\"${CMAKE_INSTALL_PREFIX}/${Pong_NAME}.app\" \"\" \"\")
  ")

endif()

install(TARGETS ${Pong_NAME}
        BUNDLE DESTINATION "."
        RUNTIME DESTINATION "."
        ARCHIVE DESTINATION "."
        LIBRARY DESTINATION ".")

if(WIN32 AND SDL2_RUNTIME_LIBRARY)

  # Include DLL files
  install(FILES ${SDL2_RUNTIME_LIBRARY}
                ${SDL2_MIXER_RUNTIME_LIBRARY}
                ${SDL2_TTF_RUNTIME_LIBRARY}
          DESTINATION ".")

endif()
