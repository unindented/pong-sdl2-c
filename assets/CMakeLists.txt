add_custom_target(assets ALL DEPENDS
                  ${Pong_MACOSX_APP_ICON}
                  ${Pong_MACOSX_INSTALLER_ICON}
                  ${Pong_MACOSX_INSTALLER_BACKGROUND}
                  ${Pong_WIN_APP_ICON}
                  ${Pong_WIN_INSTALLER_ICON}
                  ${Pong_WIN_INSTALLER_HEADER})

if(APPLE)

  add_custom_command(OUTPUT ${Pong_MACOSX_APP_ICON}
                     DEPENDS ${Pong_MACOSX_APP_ICON_FILES}
                     COMMAND iconutil ${Pong_MACOSX_APP_ICON_FOLDER} -c icns -o ${Pong_MACOSX_APP_ICON}
                     COMMENT "Generate macOS app icon")

  add_custom_command(OUTPUT ${Pong_MACOSX_INSTALLER_ICON}
                     DEPENDS ${Pong_MACOSX_INSTALLER_ICON_FILES}
                     COMMAND iconutil ${Pong_MACOSX_INSTALLER_ICON_FOLDER} -c icns -o ${Pong_MACOSX_INSTALLER_ICON}
                     COMMENT "Generate macOS installer icon")

  add_custom_command(OUTPUT ${Pong_MACOSX_INSTALLER_BACKGROUND}
                     DEPENDS ${Pong_MACOSX_INSTALLER_BACKGROUND_FILES}
                     COMMAND tiffutil -cathidpicheck ${Pong_MACOSX_INSTALLER_BACKGROUND_FILES} -out ${Pong_MACOSX_INSTALLER_BACKGROUND}
                     COMMENT "Generate macOS installer background")

  configure_file(${Pong_MACOSX_INSTALLER_SCRIPT_IN} ${Pong_MACOSX_INSTALLER_SCRIPT})

elseif(WIN32)

  add_custom_command(OUTPUT ${Pong_WIN_APP_ICON}
                     DEPENDS ${Pong_WIN_APP_ICON_FILES}
                     COMMAND convert ${Pong_WIN_APP_ICON_FILES} ${Pong_WIN_APP_ICON}
                     COMMENT "Generate Windows app icon")

  add_custom_command(OUTPUT ${Pong_WIN_INSTALLER_ICON}
                     DEPENDS ${Pong_WIN_INSTALLER_ICON_FILES}
                     COMMAND convert ${Pong_WIN_INSTALLER_ICON_FILES} ${Pong_WIN_INSTALLER_ICON}
                     COMMENT "Generate Windows installer icon")

  add_custom_command(OUTPUT ${Pong_WIN_INSTALLER_HEADER}
                     DEPENDS ${Pong_WIN_INSTALLER_HEADER_FILE}
                     COMMAND convert ${Pong_WIN_INSTALLER_HEADER_FILE} BMP3:${Pong_WIN_INSTALLER_HEADER}
                     COMMENT "Generate Windows installer header")

  configure_file(${Pong_WIN_APP_INFO_IN} ${Pong_WIN_APP_INFO})

endif()
