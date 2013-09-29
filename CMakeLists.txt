cmake_minimum_required(VERSION 2.8)

project(Cprimes)

option(BUILD_DOCUMENTATION "Generate docs with Doxygen." OFF)
option(BUILD_BENCHMARKS    "Build the benchmarks. Requires Celero." OFF)

set(CPRIMESLIB "cprimes")
find_library(GMPLIB gmp)
if(BUILD_BENCHMARKS)
	find_library(CELERO celero)
endif()

if(MSVC)
	add_definitions("-D_CRT_SECURE_NO_WARNINGS")
else()
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -std=c89")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11")
endif()

include_directories(cprimeslib/include)

set(BIN_DIR ${CMAKE_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${BIN_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
	${BIN_DIR}
	CACHE PATH
	"Something"
	)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
	${BIN_DIR}
	CACHE PATH
	"Something"
	)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
	${BIN_DIR}
	CACHE PATH
	"Something"
	)

add_subdirectory(cprimeslib)
add_subdirectory(bindings)
add_subdirectory(tests)
if(BUILD_BENCHMARKS)
	add_subdirectory(benchmarks)
endif()

if(BUILD_DOCUMENTATION)
	find_package(Doxygen)
	if(NOT DOXYGEN_FOUND)
		message(FATAL_ERROR "Doxygen is needed to generate docs.")
	endif()
	configure_file(doxygen.config ${CMAKE_BINARY_DIR}/Doxyfile @ONLY IMMEDIATE)
	add_custom_target(
		docs ALL
		COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
		SOURCES ${CMAKE_BINARY_DIR}/Doxyfile
	)
endif()
