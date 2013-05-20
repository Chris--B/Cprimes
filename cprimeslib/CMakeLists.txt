cmake_minimum_required(VERSION 2.8)

set(
	sources
	source/eratos.c
	source/estimate.c
	source/lucas_lehmer.c
	source/miller_rabin.c
	source/seg_eratos.c
)

set(
	includes
	include/defines.h
	include/eratos.h
	include/estimate.h
	include/lucas_lehmer.h
	include/miller_rabin.h
	include/seg_eratos.h
)

if("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
	set(includes ${includes} include/windows-defines.h)
else()
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DMAKINGDLL")
endif()

add_library(
	cprimes
	SHARED
	${sources}
	${includes}
)

target_link_libraries(
	cprimes
	gmp
	)