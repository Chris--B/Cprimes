cmake_minimum_required(VERSION 3.0)

project(CprimesWorkspace LANGUAGES C)

# Find a GMP install
# Linux and macOS targets should be able to install this from their
# package manager (apt, brew, etc), or just build from source.
find_library(GMPLIB gmp)
if (NOT GMPLIB)
	# Windows isn't so simple
	# We use pre-built static binaries
	if (WIN32)
		# Fall back to FetchContent to pull down known binaries
		add_subdirectory(gmp)
	endif()
endif()

# Include the main library
add_subdirectory(cprimeslib)

# Bindings for Python
add_subdirectory(bindings)

# Include tests last, since some of them depend on the bindings
add_subdirectory(tests cprimestests)

option(BUILD_DOCUMENTATION "Generate HTML docs with Doxygen" OFF)
if(BUILD_DOCUMENTATION)
	find_package(Doxygen)

	if(NOT DOXYGEN_FOUND)
		message(FATAL_ERROR "Doxygen is needed to generate docs.")
	endif()

	configure_file(doxygen.config ${CMAKE_BINARY_DIR}/Doxyfile @ONLY IMMEDIATE)

	add_custom_target(docs ALL
		COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
		SOURCES ${CMAKE_BINARY_DIR}/Doxyfile
	)
endif()
