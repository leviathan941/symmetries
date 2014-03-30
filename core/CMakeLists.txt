# CMakeLists for 'core' sub-project Symmetries
#
# Symmetries
# Copyright (C) 2013, 2014 Alexey Kuzin <amkuzink@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 2.8)
project(core)

set(CORE_HEADERS
	AffineConnection.h
	MatrixVectorExp.h
	Expression.h
	Equation.h
	Item.h
	MatrixVector.h
	VariablesMap.h
	Exceptions.h
	)

set(CORE_SOURCES
	AffineConnection.cpp
	MatrixVectorExp.cpp
	Expression.cpp
	Equation.cpp
	Item.cpp
	VariablesMap.cpp
	)

include_directories(${COMMON_INCLUDE_DIRS})

add_library(${PROJECT_NAME} ${CORE_SOURCES} ${CORE_HEADERS})
