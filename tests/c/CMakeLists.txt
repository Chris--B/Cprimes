cmake_minimum_required(VERSION 3.0)
project(CprimesTestsC LANGUAGES C)

###########################
# CuTest Testing Framework
add_library(cutest STATIC
    CuTest.h
    CuTest.c
)

# This library needs variadic macros
set_property(TARGET cutest PROPERTY C_STANDARD 99)

target_include_directories(cutest
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Disable all warnings - we're not going to fix them
if (MSVC)
    target_compile_options(cutest PRIVATE "/w")
else()
    target_compile_options(cutest PRIVATE "-w")
endif()

#################
# Unit Tests in C
add_executable(tests-c)

set_property(TARGET tests-c PROPERTY C_STANDARD 99)

target_sources(tests-c
    PRIVATE
        # Source
        all_tests.c
        test_eratos.c
        test_estimate.c
        test_miller_rabin.c
        test_lucas_lehmer.c
)

target_compile_definitions(tests-c
    PRIVATE
        _CRT_SECURE_NO_WARNINGS=1
)

target_link_libraries(tests-c
    PRIVATE
        cutest
        cprimes
)

set_target_properties(tests-c
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:cprimes>
)
