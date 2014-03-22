# CMakeLists for 'application' sub-project of Symmetries
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

cmake_minimum_required(VERSION 2.8.10)
project(application)

set(APPLICATION_HEADERS
	MainWindow.h
	)

set(APPLICATION_SOURCES
	main.cpp
	MainWindow.cpp
	)

set(APPLICATION_LIBS
	core
	file
	)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)

include_directories(
	${COMMON_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/core
	${CMAKE_SOURCE_DIR}/file
	)

add_executable(${GENERIC_PROJECT_NAME} ${APPLICATION_SOURCES} ${APPLICATION_HEADERS})
target_link_libraries(${GENERIC_PROJECT_NAME} ${APPLICATION_LIBS})
qt5_use_modules(${GENERIC_PROJECT_NAME} Widgets)
