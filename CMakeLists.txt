# Top-level CMakeLists for Symmetries project
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

cmake_minimum_required(VERSION 2.8.11)
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
