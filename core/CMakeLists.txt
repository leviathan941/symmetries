cmake_minimum_required(VERSION 2.8)
project(core)

set(CMAKE_BUILD_TYPE Debug)

set(CORE_HEADERS
	AffineConnection.h
	MatrixVectorExp.h
	Expression.h
#	Equation.h
	Item.h
	MatrixVector.h
	VariablesMap.h
	Exceptions.h
	)

set(CORE_SOURCES
	AffineConnection.cpp
	MatrixVectorExp.cpp
	Expression.cpp
#	Equation.cpp
	Item.cpp
	VariablesMap.cpp
	)

include_directories(${COMMON_INCLUDE_DIRS})

add_library(${PROJECT_NAME} ${CORE_SOURCES} ${CORE_HEADERS})
