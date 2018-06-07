find_path(SDL2_INCLUDE_DIR SDL.h
          HINTS ENV SDL2DIR
          PATH_SUFFIXES include/SDL2 include
          PATHS ${SDL2_PATH})

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(PATH_SUFFIXES lib64 lib/x64 lib)
else()
  set(PATH_SUFFIXES lib/x86 lib)
endif()

find_library(SDL2_LIBRARY_TEMP
             NAMES SDL2
             HINTS ENV SDL2DIR
             PATH_SUFFIXES ${PATH_SUFFIXES}
             PATHS ${SDL2_PATH})

if(NOT SDL2_BUILDING_LIBRARY)
  if(NOT ${SDL2_INCLUDE_DIR} MATCHES ".framework")
    find_library(SDL2MAIN_LIBRARY
                 NAMES SDL2main
                 HINTS ENV SDL2DIR
                 PATH_SUFFIXES ${PATH_SUFFIXES}
                 PATHS ${SDL2_PATH})
  endif()
endif()

if(NOT APPLE)
  find_package(Threads)
endif()

if(MINGW)
  set(MINGW32_LIBRARY mingw32 "-mwindows" CACHE STRING "MinGW library")
endif()

if(SDL2_LIBRARY_TEMP)
  if(NOT SDL2_BUILDING_LIBRARY)
    if(SDL2MAIN_LIBRARY)
      set(SDL2_LIBRARY_TEMP ${SDL2MAIN_LIBRARY} ${SDL2_LIBRARY_TEMP})
    endif()
  endif()

  if(APPLE)
    set(SDL2_LIBRARY_TEMP ${SDL2_LIBRARY_TEMP} "-framework Cocoa")
  endif()

  if(NOT APPLE)
    set(SDL2_LIBRARY_TEMP ${SDL2_LIBRARY_TEMP} ${CMAKE_THREAD_LIBS_INIT})
  endif()

  if(MINGW)
    set(SDL2_LIBRARY_TEMP ${MINGW32_LIBRARY} ${SDL2_LIBRARY_TEMP})
  endif()

  set(SDL2_LIBRARY ${SDL2_LIBRARY_TEMP}
      CACHE STRING "Where the SDL2 Library can be found")
  set(SDL2_LIBRARY_TEMP ${SDL2_LIBRARY_TEMP}
      CACHE INTERNAL "")

  if(WIN32 AND SDL2_LIBRARY)
    find_file(SDL2_RUNTIME_LIBRARY
              NAMES SDL2.dll libSDL2.dll
              HINTS ENV SDL2DIR
              PATH_SUFFIXES bin ${PATH_SUFFIXES}
              PATHS ${SDL2_PATH})
  endif()
endif()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(SDL2
                                  REQUIRED_VARS SDL2_LIBRARY SDL2_INCLUDE_DIR)
