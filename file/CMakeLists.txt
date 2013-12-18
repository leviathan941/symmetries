cmake_minimum_required(VERSION 2.8)
project(file)

set(FILE_HEADERS
	FileReader.h
	)

set(FILE_SOURCES
	FileReader.cpp
	)

set(FILE_LIBS
	${Boost_LIBRARIES}
	)

include_directories(${COMMON_INCLUDE_DIRS})

add_library(${PROJECT_NAME} ${FILE_SOURCES} ${FILE_HEADERS})
target_link_libraries(${PROJECT_NAME} ${FILE_LIBS})
