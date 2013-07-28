cmake_minimum_required (VERSION 2.6)
project (OALWrapper)

set(OALWrapper_VERSION_MAJOR 1)
set(OALWrapper_VERSION_MINOR 0)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeScripts)

SET(PRIVATE_LIB_DIR
    CACHE PATH "Location of local private library path to use"
)
IF(NOT APP_PRIVATE_LIB_DIR AND PRIVATE_LIB_DIR)
    SET(APP_PRIVATE_LIB_DIR ${PRIVATE_LIB_DIR})
ENDIF()

OPTION(USE_SDL2 "Use SDL2 instead of SDL1.2" OFF)

IF(APP_PRIVATE_LIB_DIR AND "${CMAKE_SYSTEM}" MATCHES "Linux")
    IF(NOT EXISTS ${APP_PRIVATE_LIB_DIR}/include)
        MESSAGE(FATAL_ERROR "folder named include not found in private lib dir ${APP_PRIVATE_LIB_DIR}")
    ENDIF()
    SET(EXTRA_INCLUDE_DIR ${APP_PRIVATE_LIB_DIR}/include)
    IF(NOT PRIVATE_LIB_SUFFIX)
        IF(CMAKE_SIZEOF_VOID_P MATCHES "8" AND NOT(FORCE32))
            if(EXISTS ${APP_PRIVATE_LIB_DIR}/linux64)
                SET(PRIVATE_LIB_SUFFIX "linux64")
            else(EXISTS ${APP_PRIVATE_LIB_DIR}/lib64)
                SET(PRIVATE_LIB_SUFFIX "lib64")
            endif()
        ELSE()
            if(EXISTS ${APP_PRIVATE_LIB_DIR}/linux)
                SET(PRIVATE_LIB_SUFFIX "linux")
            else(EXISTS ${APP_PRIVATE_LIB_DIR}/lib)
                SET(PRIVATE_LIB_SUFFIX "lib")
            endif()
        ENDIF()
    ENDIF()
    IF(NOT PRIVATE_LIB_SUFFIX)
        MESSAGE(FATAL_ERROR "could not find lib directory in private lib dir ${APP_PRIVATE_LIB_DIR}")
    ENDIF()

    IF(EXISTS ${APP_PRIVATE_LIB_DIR}/${PRIVATE_LIB_SUFFIX}/libogg.so)
        SET(OGG_LIBRARY "${APP_PRIVATE_LIB_DIR}/${PRIVATE_LIB_SUFFIX}/libogg.so" CACHE FILEPATH "Ogg")
    ENDIF()
    IF(NOT OGG_LIBRARY)
        MESSAGE(FATAL_ERROR "Could not find ogg library")
    ENDIF()

    IF(EXISTS ${APP_PRIVATE_LIB_DIR}/${PRIVATE_LIB_SUFFIX}/libvorbis.so)
        SET(VORBIS_LIBRARY "${APP_PRIVATE_LIB_DIR}/${PRIVATE_LIB_SUFFIX}/libvorbis.so" CACHE FILEPATH "Vorbis")
    ENDIF()
    IF(NOT VORBIS_LIBRARY)
        MESSAGE(FATAL_ERROR "Could not find vorbis library")
    ENDIF()

    IF(EXISTS ${APP_PRIVATE_LIB_DIR}/${PRIVATE_LIB_SUFFIX}/libvorbisfile.so)
        SET(VORBISFILE_LIBRARY "${APP_PRIVATE_LIB_DIR}/${PRIVATE_LIB_SUFFIX}/libvorbisfile.so" CACHE FILEPATH "VorbisFile")
    ENDIF()
    IF(NOT VORBISFILE_LIBRARY)
        MESSAGE(FATAL_ERROR "Could not find vorbisfile library")
    ENDIF()

    IF(EXISTS ${APP_PRIVATE_LIB_DIR}/${PRIVATE_LIB_SUFFIX}/libopenal.so)
        SET(OPENAL_LIBRARY "${APP_PRIVATE_LIB_DIR}/${PRIVATE_LIB_SUFFIX}/libopenal.so" CACHE FILEPATH "OpenAL")
    ENDIF()
    IF(NOT OPENAL_LIBRARY)
        MESSAGE(FATAL_ERROR "Could not find openal library")
    ENDIF()

    IF(EXISTS ${APP_PRIVATE_LIB_DIR}/${PRIVATE_LIB_SUFFIX}/libSDL.so)
        SET(OPENAL_LIBRARY "${APP_PRIVATE_LIB_DIR}/${PRIVATE_LIB_SUFFIX}/libSDL.so" CACHE FILEPATH "SDL")
    ENDIF()
    IF(NOT OPENAL_LIBRARY)
        MESSAGE(FATAL_ERROR "Could not find SDL library")
    ENDIF()
ELSEIF(APP_PRIVATE_LIB_DIR AND APPLE)
    FIND_LIBRARY(OGG_LIBRARY Ogg PATHS ${APP_PRIVATE_LIB_DIR} NO_DEFAULT_PATH)
    FIND_LIBRARY(VORBIS_LIBRARY Vorbis PATHS ${APP_PRIVATE_LIB_DIR} NO_DEFAULT_PATH)
    IF(USE_SDL2)
        FIND_LIBRARY(SDL_LIBRARY SDL2 PATHS ${APP_PRIVATE_LIB_DIR} NO_DEFAULT_PATH)
    ELSE()
        FIND_LIBRARY(SDL_LIBRARY SDL PATHS ${APP_PRIVATE_LIB_DIR} NO_DEFAULT_PATH)
    ENDIF()
    FIND_PATH(SDL_INCLUDE_DIR SDL.h
        PATHS ${SDL_LIBRARY}
        PATH_SUFFIXES Headers
        NO_DEFAULT_PATH)
    INCLUDE_DIRECTORIES(
        ${SDL_INCLUDE_DIR}
    )
    FIND_PACKAGE(OpenAL)
ELSE()
    FIND_PACKAGE(OGG)
    FIND_PACKAGE(Vorbis)
    IF(NOT(APPLE))
        FIND_PACKAGE(VorbisFile)
    ENDIF()
    FIND_PACKAGE(OpenAL)
    IF(USE_SDL2)
        FIND_PACKAGE(SDL2)
    ELSE()
        FIND_PACKAGE(SDL)
    ENDIF()

    INCLUDE_DIRECTORIES(
        ${OGG_INCLUDE_DIR}
        ${VORBIS_INCLUDE_DIR}
        ${VORBISFILE_INCLUDE_DIR}
        ${OPENAL_INCLUDE_DIR}
        ${SDL_INCLUDE_DIR}
    )
ENDIF()

include_directories(
    include
    ${EXTRA_INCLUDE_DIR}
)
SET(all_sources
    sources/OAL_AudioData.cpp
    sources/OAL_Buffer.cpp
    sources/OAL_Device.cpp
    sources/OAL_Effect.cpp
    sources/OAL_Effect_Reverb.cpp
    sources/OAL_EffectSlot.cpp
    sources/OAL_EFX.cpp
    sources/OAL_EFXManager.cpp
    sources/OAL_Filter.cpp
    sources/OAL_Helper.cpp
    sources/OAL_Init.cpp
    sources/OAL_Loaders.cpp
    sources/OAL_LoggerObject.cpp
    sources/OAL_OggSample.cpp
    sources/OAL_OggStream.cpp
    sources/OAL_WAVSample.cpp
    sources/OAL_CustomStream.cpp
    sources/OAL_Playback.cpp
    sources/OAL_Sample.cpp
    sources/OAL_Source.cpp
    sources/OAL_SourceManager.cpp
    sources/OAL_Stream.cpp
    sources/OAL_Types.cpp
)

IF(USE_SDL2)
    add_definitions(-DUSE_SDL2)
ENDIF()

add_library(OALWrapper STATIC ${all_sources})
TARGET_LINK_LIBRARIES(OALWrapper
    ${OGG_LIBRARY}
    ${VORBIS_LIBRARY}
    ${VORBISFILE_LIBRARY}
    ${OPENAL_LIBRARY}
    ${SDL_LIBRARY}
)

ADD_EXECUTABLE(SimpleTest EXCLUDE_FROM_ALL tests/Simple/main.cpp)
TARGET_LINK_LIBRARIES(SimpleTest OALWrapper)

ADD_EXECUTABLE(PlaySound EXCLUDE_FROM_ALL tests/PlaySound/main.cpp)
TARGET_LINK_LIBRARIES(PlaySound OALWrapper)

ADD_EXECUTABLE(Playlist EXCLUDE_FROM_ALL tests/Playlist/main.cpp)
TARGET_LINK_LIBRARIES(Playlist OALWrapper)

ADD_EXECUTABLE(CustomStream EXCLUDE_FROM_ALL tests/CustomStream/main.cpp)
TARGET_LINK_LIBRARIES(CustomStream OALWrapper)

# Exports
SET(OALWRAPPER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
