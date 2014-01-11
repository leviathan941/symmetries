cmake_minimum_required(VERSION 2.8)
project(application)

set(APPLICATION_HEADERS
	)

set(APPLICATION_SOURCES
	main.cpp
	)

set(APPLICATION_LIBS
	core
	file
	)

include_directories(
	${COMMON_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/core
	${CMAKE_SOURCE_DIR}/file
	)


add_executable(${GENERIC_PROJECT_NAME} ${APPLICATION_SOURCES} ${APPLICATION_HEADERS})
target_link_libraries(${GENERIC_PROJECT_NAME} ${APPLICATION_LIBS})
