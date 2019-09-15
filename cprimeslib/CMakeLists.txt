cmake_minimum_required(VERSION 3.0)
project(Cprimes LANGUAGES C)

add_library(cprimes SHARED)

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

		# Public headers
		include/eratos.h
		include/estimate.h
		include/lucas_lehmer.h
		include/miller_rabin.h

		# Private headers
		source/util.h
)

target_compile_definitions(cprimes
	PRIVATE
		CPRIMES_BUILDING_DLL=1
	INTERFACE
		CPRIMES_BUILDING_DLL=0
)

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
