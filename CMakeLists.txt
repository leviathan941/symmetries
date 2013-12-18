cmake_minimum_required(VERSION 2.8)
project(Symmetries)

set(SYMMETRIES_HEADERS
	)

set(SYMMETRIES_SOURCES
	main.cpp
	)

set(SYMMETRIES_LIBS
	core
	file
	)

set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS filesystem system REQUIRED)

set(COMMON_INCLUDE_DIRS
	${COMMON_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
	)

include_directories(
	${COMMON_INCLUDE_DIRS}
	core
	file
	)

add_subdirectory("core")
add_subdirectory("file")

add_executable(${PROJECT_NAME} ${SYMMETRIES_SOURCES} ${SYMMETRIES_HEADERS})
target_link_libraries(${PROJECT_NAME} ${SYMMETRIES_LIBS})
