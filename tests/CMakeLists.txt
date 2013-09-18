
# Purely aesthetic
set(HERE ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
	set(TESTS_FILE run-all-tests.bat)
else()
	set(TESTS_FILE run-all-tests)
endif()


add_custom_target(copy_tests_files
	ALL
	DEPENDS ${HERE}/${TESTS_FILE}
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${HERE}/${TESTS_FILE} ${BIN_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${HERE}/python/tests-python.py ${BIN_DIR})


set(sources
	c/AllTests.c
	c/CuTest.c
	c/test_eratos.c
	c/test_miller_rabin.c
	c/test_estimate.c
	c/test_lucas_lehmer.c
)

set(includes
	c/CuTest.h
)

add_executable(
	tests-c
	${sources}
	${includes}
)

target_link_libraries(tests-c ${CPRIMESLIB})

