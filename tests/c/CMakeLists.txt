cmake_minimum_required(VERSION 2.8)

set(
	sources
	AllTests.c
	CuTest.c
	test_eratos.c
	test_miller_rabin.c
)

set(
	includes
	CuTest.h
)

add_executable(
	tests-c
	${includes}
	${sources}
)

target_link_libraries(tests-c cprimes)

