find_path(SDL2_MIXER_INCLUDE_DIR SDL_mixer.h
          HINTS ENV SDL2MIXERDIR
                ENV SDL2DIR
          PATH_SUFFIXES SDL2 include/SDL2 include
          PATHS ${SDL2_MIXER_PATH})

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(PATH_SUFFIXES lib/x64)
else()
  set(PATH_SUFFIXES lib/x86)
endif()

find_library(SDL2_MIXER_LIBRARY
             NAMES SDL2_mixer
             HINTS ENV SDL2MIXERDIR
                   ENV SDL2DIR
             PATH_SUFFIXES lib ${PATH_SUFFIXES}
             PATHS ${SDL2_MIXER_PATH})

if(SDL2_MIXER_INCLUDE_DIR AND EXISTS "${SDL2_MIXER_INCLUDE_DIR}/SDL_mixer.h")
  file(STRINGS "${SDL2_MIXER_INCLUDE_DIR}/SDL_mixer.h" SDL2_MIXER_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SDL_MIXER_MAJOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL2_MIXER_INCLUDE_DIR}/SDL_mixer.h" SDL2_MIXER_VERSION_MINOR_LINE REGEX "^#define[ \t]+SDL_MIXER_MINOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL2_MIXER_INCLUDE_DIR}/SDL_mixer.h" SDL2_MIXER_VERSION_PATCH_LINE REGEX "^#define[ \t]+SDL_MIXER_PATCHLEVEL[ \t]+[0-9]+$")
  string(REGEX REPLACE "^#define[ \t]+SDL_MIXER_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_MIXER_VERSION_MAJOR "${SDL2_MIXER_VERSION_MAJOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL_MIXER_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_MIXER_VERSION_MINOR "${SDL2_MIXER_VERSION_MINOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL_MIXER_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" SDL2_MIXER_VERSION_PATCH "${SDL2_MIXER_VERSION_PATCH_LINE}")
  set(SDL2_MIXER_VERSION_STRING ${SDL2_MIXER_VERSION_MAJOR}.${SDL2_MIXER_VERSION_MINOR}.${SDL2_MIXER_VERSION_PATCH})
  unset(SDL2_MIXER_VERSION_MAJOR_LINE)
  unset(SDL2_MIXER_VERSION_MINOR_LINE)
  unset(SDL2_MIXER_VERSION_PATCH_LINE)
  unset(SDL2_MIXER_VERSION_MAJOR)
  unset(SDL2_MIXER_VERSION_MINOR)
  unset(SDL2_MIXER_VERSION_PATCH)
endif()

if(WIN32 AND SDL2_MIXER_LIBRARY)
  find_file(SDL2_MIXER_RUNTIME_LIBRARY
            NAMES SDL2_mixer.dll libSDL2_mixer.dll
            HINTS ENV SDL2MIXERDIR
                  ENV SDL2DIR
            PATH_SUFFIXES bin ${PATH_SUFFIXES}
            PATHS ${SDL2_MIXER_PATH})
endif()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(SDL2_mixer
                                  REQUIRED_VARS SDL2_MIXER_LIBRARY SDL2_MIXER_INCLUDE_DIR
                                  VERSION_VAR SDL2_MIXER_VERSION_STRING)
