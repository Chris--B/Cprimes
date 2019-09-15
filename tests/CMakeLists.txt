cmake_minimum_required(VERSION 3.0)
project(CprimesTests LANGUAGES C)

add_subdirectory(c)

# No CMakeLists files in `python

if(WIN32)
    set(OS_TESTS_RUNNER run-all-tests.bat)
else()
    set(OS_TESTS_RUNNER run-all-tests)
endif()

add_custom_target(copy_tests_files ALL
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${OS_TESTS_RUNNER}
    COMMENT "Copying Unit tests and tests runner scripts"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/${OS_TESTS_RUNNER}     $<TARGET_FILE_DIR:cprimes>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/python/tests-python.py $<TARGET_FILE_DIR:cprimes>
)
