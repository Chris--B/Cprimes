cmake_minimum_required(VERSION 3.0)
project(Cprimes LANGUAGES C)

add_library(cprimes)

set_property(TARGET cprimes PROPERTY C_STANDARD 89)

target_include_directories(cprimes
	PUBLIC
		include
)

target_sources(cprimes
	PRIVATE
		# Implementation files
		source/eratos.c
		source/estimate.c
		source/lucas_lehmer.c
		source/miller_rabin.c

		# Public header
		include/cprimes.h

		# Private headers
		source/util.h
)

if (MSVC)
	target_compile_options(cprimes
		PRIVATE
			/W4 /WX
	)
else()
	target_compile_options(cprimes
		PRIVATE
			-Wall -Wextra -Werror -pedantic
	)
endif()

if (${BUILD_SHARED_LIBS})
	target_compile_definitions(cprimes
		PUBLIC
			CPRIMES_USING_DLL=1
		PRIVATE
			CPRIMES_BUILDING_DLL=1
		INTERFACE
			CPRIMES_BUILDING_DLL=0
	)
endif()

set_target_properties(cprimes
	PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(cprimes
	PRIVATE
		${GMPLIB}
)
