cmake_minimum_required(VERSION 2.8)
project(symmetries)

set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS filesystem system REQUIRED)

set(COMMON_INCLUDE_DIRS
	${COMMON_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
	)

add_definitions(
	-std=c++11
	)

set(CMAKE_BUILD_TYPE Debug)
set(GENERIC_PROJECT_NAME ${PROJECT_NAME})

add_subdirectory("core")
add_subdirectory("file")
add_subdirectory("application")
