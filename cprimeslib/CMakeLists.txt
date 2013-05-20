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
	include/eratos.h
	include/estimate.h
	include/lucas_lehmer.h
	include/miller_rabin.h
	include/seg_eratos.h
)

# MinGW
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DMAKINGDLL")

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
