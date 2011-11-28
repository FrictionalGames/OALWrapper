cmake_minimum_required (VERSION 2.6)
project (OALWrapper)

set(OALWrapper_VERSION_MAJOR 1)
set(OALWrapper_VERSION_MINOR 0)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeScripts)

OPTION(WITH_ALUT "Include alut WAVE loading" OFF)

SET(PRIVATE_LIB_DIR
    CACHE PATH "Location of local private library path to use"
)

IF(PRIVATE_LIB_DIR)
    IF(NOT EXISTS ${PRIVATE_LIB_DIR}/include)
        MESSAGE(FATAL_ERROR "folder named include not found in private lib dir")
    ENDIF()
    INCLUDE_DIRECTORIES(
        ${PRIVATE_LIB_DIR}/include}
    )
    FIND_LIBRARY(OGG_LIBRARY
        ogg
        PATH_SUFFIXES lib lib64 linux linux64
        NO_DEFAULT_PATH
        PATHS ${PRIVATE_LIB_DIR}
    )
    IF(OGG_LIBRARY STREQUAL "OGG_LIBRARY-NOTFOUND")
        MESSAGE(FATAL_ERROR "Could not find ogg library")
    ENDIF()

    FIND_LIBRARY(VORBIS_LIBRARY
        vorbis
        PATH_SUFFIXES lib lib64 linux linux64
        NO_DEFAULT_PATH
        PATHS ${PRIVATE_LIB_DIR}
    )
    IF(VORBIS_LIBRARY STREQUAL "VORBIS_LIBRARY-NOTFOUND")
        MESSAGE(FATAL_ERROR "Could not find vorbis library")
    ENDIF()

    FIND_LIBRARY(VORBISFILE_LIBRARY
        vorbisfile
        PATH_SUFFIXES lib lib64 linux linux64
        NO_DEFAULT_PATH
        PATHS ${PRIVATE_LIB_DIR}
    )
    IF(VORBISFILE_LIBRARY STREQUAL "VORBISFILE_LIBRARY-NOTFOUND")
        MESSAGE(FATAL_ERROR "Could not find vorbisfile library")
    ENDIF()

    IF(WITH_ALUT)
        FIND_LIBRARY(ALUT_LIBRARY
            alut
            PATH_SUFFIXES lib lib64 linux linux64
            NO_DEFAULT_PATH
            PATHS ${PRIVATE_LIB_DIR}
        )
        IF(ALUT_LIBRARY STREQUAL "ALUT_LIBRARY-NOTFOUND")
            MESSAGE(FATAL_ERROR "Could not find alut library")
        ENDIF()
    ENDIF()

    FIND_LIBRARY(OPENAL_LIBRARY
        openal
        PATH_SUFFIXES lib lib64 linux linux64
        NO_DEFAULT_PATH
        PATHS ${PRIVATE_LIB_DIR}
    )
    IF(OPENAL_LIBRARY STREQUAL "OPENAL_LIBRARY-NOTFOUND")
        MESSAGE(FATAL_ERROR "Could not find openal library")
    ENDIF()
ELSE()
    FIND_PACKAGE(OGG)
    FIND_PACKAGE(Vorbis)
    FIND_PACKAGE(VorbisFile)
    FIND_PACKAGE(OpenAL)

    IF(WITH_ALUT)
        FIND_PACKAGE(ALUT)
    ENDIF()
    INCLUDE_DIRECTORIES(
        ${OGG_INCLUDE_DIR}
        ${VORBIS_INCLUDE_DIR}
        ${VORBISFILE_INCLUDE_DIR}
        ${OPENAL_INCLUDE_DIR}
    )
ENDIF()

IF(WITH_ALUT)
    ADD_DEFINITIONS(-DWITH_ALUT)
ENDIF()

include_directories(
	include
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
    sources/OAL_OggHelper.cpp
    sources/OAL_OggSample.cpp
    sources/OAL_OggStream.cpp
    sources/OAL_Playback.cpp
    sources/OAL_Sample.cpp
    sources/OAL_Source.cpp
    sources/OAL_SourceManager.cpp
    sources/OAL_Stream.cpp
    sources/OAL_Types.cpp
)

IF(WITH_ALUT)
    LIST(APPEND all_sources
        sources/OAL_WAVSample.cpp
    )
ENDIF()

add_library(OALWrapper STATIC ${all_sources})
TARGET_LINK_LIBRARIES(OALWrapper
    ${OGG_LIBRARY}
    ${VORBIS_LIBRARY}
    ${VORBISFILE_LIBRARY}
    ${ALUT_LIBRARY}
    ${OPENAL_LIBRARY}
    SDL
)

ADD_EXECUTABLE(SimpleTest
    tests/Simple/main.cpp
)
TARGET_LINK_LIBRARIES(SimpleTest
    OALWrapper
)