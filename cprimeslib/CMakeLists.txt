cmake_minimum_required(VERSION 2.8)

set(
	sources
	source/eratos.c
	source/estimate.c
	source/lucas_lehmer.c
	source/miller_rabin.c
)

set(
	includes
	include/defines.h
	include/eratos.h
	include/estimate.h
	include/lucas_lehmer.h
	include/miller_rabin.h
)

if("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
	set(includes ${includes} include/windows-defines.h)
else()
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
endif()

add_library(
	${CPRIMESLIB}
	SHARED
	${sources}
	${includes}
)

target_link_libraries(
	${CPRIMESLIB}
	${GMPLIB}
	${MATH_LIB}
	)
