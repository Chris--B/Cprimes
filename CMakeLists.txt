cmake_minimum_required(VERSION 2.8)

project(Cprimes)

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
	set(OPTIMIZE_FLAGS "-O2 -DNDEBUG")
	set(WARNING_FLAGS "-Wall -Wextra")
	set(CMAKE_C_FLAGS "-ansi ${OPTIMIZE_FLAGS} ${WARNING_FLAGS}")
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
	set(CMAKE_C_FLAGS "/D_CRT_SECURE_NO_WARNINGS")
endif()

include_directories(cprimeslib/include)

set(BIN_DIR ${CMAKE_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${BIN_DIR})

set(
	CMAKE_ARCHIVE_OUTPUT_DIRECTORY
	${BIN_DIR}
	CACHE PATH
	"Something"
	)
set(
	CMAKE_LIBRARY_OUTPUT_DIRECTORY
	${BIN_DIR}
	CACHE PATH
	"Something"
	)
set(
	CMAKE_RUNTIME_OUTPUT_DIRECTORY
	${BIN_DIR}
	CACHE PATH
	"Something"
	)

add_subdirectory(bindings)
add_subdirectory(cprimeslib)
add_subdirectory(tests)

option(BUILD_DOCUMENTATION "Generate HTML docs with Doxygen" OFF)
if(BUILD_DOCUMENTATION)
	find_package(Doxygen)
	if(NOT DOXYGEN_FOUND)
		message(FATAL_ERROR "Doxygen is needed to generate docs.")
	endif()
	configure_file(Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile @ONLY IMMEDIATE)
	add_custom_target(
		docs ALL
		COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
		SOURCES ${CMAKE_BINARY_DIR}/Doxyfile
	)
endif()
