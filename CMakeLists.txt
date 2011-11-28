cmake_minimum_required (VERSION 2.6)
project (OALWrapper)

set(OALWrapper_VERSION_MAJOR 1)
set(OALWrapper_VERSION_MINOR 0)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeScripts)

OPTION(WITH_ALUT "Include alut WAVE loading" OFF)

FIND_PACKAGE(OGG)
FIND_PACKAGE(Vorbis)
FIND_PACKAGE(VorbisFile)
FIND_PACKAGE(OpenAL)

IF(WITH_ALUT)
    FIND_PACKAGE(ALUT)
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