cmake_minimum_required(VERSION 3.6)

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.6"
    CACHE STRING "macOS deployment version" FORCE)

project("Pong"
        VERSION "0.0.1"
        DESCRIPTION "Pong clone built with SDL2 in C"
        LANGUAGES C)
set(Pong_PACKAGE "org.unindented.${PROJECT_NAME}")
set(Pong_NAME ${PROJECT_NAME})
set(Pong_READABLE_NAME "Pong Pong")
set(Pong_DESCRIPTION ${PROJECT_DESCRIPTION})
set(Pong_AUTHOR_NAME "Daniel Perez Alvarez")
set(Pong_AUTHOR_EMAIL "unindented@gmail.com")
set(Pong_HOMEPAGE_URL "https://github.com/unindented/pong-sdl2-c")
string(TIMESTAMP Pong_COPYRIGHT_YEAR "%Y")
set(Pong_COPYRIGHT "Copyright (c) ${Pong_COPYRIGHT_YEAR} ${Pong_AUTHOR_NAME}")

# Setup

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

option(BUILD_ARCH "Architecture to build for")
option(ENABLE_TESTING "Build and run tests" TRUE)

if(NOT BUILD_ARCH)
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(BUILD_ARCH 64)
  else()
    set(BUILD_ARCH 32)
  endif()
endif()

set(CMAKE_C_FLAGS "-m${BUILD_ARCH}")
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

# Sanity checks

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds are not allowed.")
endif()

message(STATUS "Generator: ${CMAKE_GENERATOR}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Build arch: ${BUILD_ARCH}bit")

# Config

include_directories(BEFORE ${CMAKE_BINARY_DIR})

set(Pong_CONFIG_IN "${CMAKE_SOURCE_DIR}/cmake/config.h.in")
set(Pong_CONFIG "${CMAKE_BINARY_DIR}/config.h")
configure_file(${Pong_CONFIG_IN} ${Pong_CONFIG})

set(Pong_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.txt")

if(APPLE)

  set(Pong_MACOSX_APP_ICON_FOLDER "${CMAKE_SOURCE_DIR}/assets/macos/app_icon.iconset")
  file(GLOB Pong_MACOSX_APP_ICON_FILES "${Pong_MACOSX_APP_ICON_FOLDER}/*")
  set(Pong_MACOSX_APP_ICON "${CMAKE_SOURCE_DIR}/assets/macos/app_icon.icns")
  get_filename_component(Pong_MACOSX_APP_ICON_NAME ${Pong_MACOSX_APP_ICON} NAME)

  set(Pong_MACOSX_INSTALLER_ICON_FOLDER "${CMAKE_SOURCE_DIR}/assets/macos/installer_icon.iconset")
  file(GLOB Pong_MACOSX_INSTALLER_ICON_FILES "${Pong_MACOSX_INSTALLER_ICON_FOLDER}/*")
  set(Pong_MACOSX_INSTALLER_ICON "${CMAKE_SOURCE_DIR}/assets/macos/installer_icon.icns")

  set(Pong_MACOSX_INSTALLER_BACKGROUND_FOLDER "${CMAKE_SOURCE_DIR}/assets/macos/installer_background")
  file(GLOB Pong_MACOSX_INSTALLER_BACKGROUND_FILES "${Pong_MACOSX_INSTALLER_BACKGROUND_FOLDER}/*")
  set(Pong_MACOSX_INSTALLER_BACKGROUND "${CMAKE_SOURCE_DIR}/assets/macos/installer_background.tiff")

  set(Pong_MACOSX_INSTALLER_SCRIPT_IN "${CMAKE_SOURCE_DIR}/assets/macos/installer_setup.scpt.in")
  set(Pong_MACOSX_INSTALLER_SCRIPT "${CMAKE_SOURCE_DIR}/assets/macos/installer_setup.scpt")

  set(Pong_MACOSX_BUNDLE_INFO_IN "${CMAKE_SOURCE_DIR}/assets/macos/Info.plist.in")

elseif(WIN32)

  set(Pong_WIN_APP_ICON_FOLDER "${CMAKE_SOURCE_DIR}/assets/windows/app_icon")
  file(GLOB Pong_WIN_APP_ICON_FILES "${Pong_WIN_APP_ICON_FOLDER}/*")
  set(Pong_WIN_APP_ICON "${CMAKE_SOURCE_DIR}/assets/windows/app_icon.ico")

  set(Pong_WIN_INSTALLER_ICON_FOLDER "${CMAKE_SOURCE_DIR}/assets/windows/installer_icon")
  file(GLOB Pong_WIN_INSTALLER_ICON_FILES "${Pong_WIN_INSTALLER_ICON_FOLDER}/*")
  set(Pong_WIN_INSTALLER_ICON "${CMAKE_SOURCE_DIR}/assets/windows/installer_icon.ico")

  set(Pong_WIN_INSTALLER_HEADER_FILE "${CMAKE_SOURCE_DIR}/assets/windows/installer_header.png")
  set(Pong_WIN_INSTALLER_HEADER "${CMAKE_SOURCE_DIR}/assets/windows\\\\installer_header.bmp")

  set(Pong_WIN_APP_INFO_IN "${CMAKE_SOURCE_DIR}/assets/windows/app_info.rc.in")
  set(Pong_WIN_APP_INFO "${CMAKE_SOURCE_DIR}/assets/windows/app_info.rc")

endif()

# Subdirectories

add_subdirectory(assets)
add_subdirectory(src)

if(ENABLE_TESTING)

  add_subdirectory(test)

  enable_testing()

  add_test(NAME test_utils COMMAND test_utils)
  add_test(NAME test_systems COMMAND test_systems)

endif()

# Packaging

set(CPACK_PACKAGE_NAME ${Pong_NAME})
set(CPACK_PACKAGE_VERSION ${Pong_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR ${Pong_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${Pong_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${Pong_VERSION_PATCH})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${Pong_DESCRIPTION})
set(CPACK_PACKAGE_VENDOR ${Pong_AUTHOR_NAME})
set(CPACK_PACKAGE_CONTACT "${Pong_AUTHOR_NAME} <${Pong_AUTHOR_EMAIL}>")
set(CPACK_PACKAGE_EXECUTABLES ${Pong_NAME} ${Pong_READABLE_NAME})
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${Pong_NAME})
set(CPACK_PACKAGE_FILE_NAME
    "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}-${BUILD_ARCH}bit")

set(CPACK_RESOURCE_FILE_LICENSE ${Pong_LICENSE})

set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)

if(APPLE)

  set(CPACK_GENERATOR DragNDrop)

  set(CPACK_DMG_FORMAT UDBZ)
  set(CPACK_DMG_VOLUME_NAME ${Pong_READABLE_NAME})
  set(CPACK_PACKAGE_ICON ${Pong_MACOSX_INSTALLER_ICON})
  set(CPACK_DMG_BACKGROUND_IMAGE ${Pong_MACOSX_INSTALLER_BACKGROUND})
  set(CPACK_DMG_DS_STORE_SETUP_SCRIPT ${Pong_MACOSX_INSTALLER_SCRIPT})

elseif(WIN32)

  set(CPACK_GENERATOR NSIS ZIP)

  set(CPACK_PACKAGE_ICON ${Pong_WIN_INSTALLER_HEADER})
  set(CPACK_NSIS_MUI_ICON ${Pong_WIN_INSTALLER_ICON})
  set(CPACK_NSIS_MUI_UNIICON ${Pong_WIN_INSTALLER_ICON})
  set(CPACK_NSIS_URL_INFO_ABOUT ${Pong_HOMEPAGE_URL})
  set(CPACK_NSIS_EXECUTABLES_DIRECTORY ".")
  set(CPACK_NSIS_INSTALLED_ICON_NAME "${Pong_NAME}.exe")
  set(CPACK_NSIS_MUI_FINISHPAGE_RUN ${CPACK_NSIS_INSTALLED_ICON_NAME})
  set(CPACK_NSIS_CREATE_ICONS_EXTRA
      "CreateShortCut '$DESKTOP\\\\${Pong_READABLE_NAME}.lnk' '$INSTDIR\\\\${CPACK_NSIS_INSTALLED_ICON_NAME}'")
  set(CPACK_NSIS_DELETE_ICONS_EXTRA
      "Delete '$DESKTOP\\\\${Pong_READABLE_NAME}.lnk'")

else()

  set(CPACK_GENERATOR TGZ)

endif()

include(CPack)
