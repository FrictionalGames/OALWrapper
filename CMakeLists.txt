cmake_minimum_required (VERSION 2.6)
project (OALWrapper)

set(OALWrapper_VERSION_MAJOR 1)
set(OALWrapper_VERSION_MINOR 0)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include 
	${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/include
	${CMAKE_CURRENT_SOURCE_DIR}/../HPL1Engine/include
)
file(GLOB_RECURSE all_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp

add_library(OALWrapper STATIC ${all_sources})

