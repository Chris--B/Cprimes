cmake_minimum_required(VERSION 3.0)
project(CprimesBindings LANGUAGES NONE)

add_custom_target(copy_python_bindings ALL
    COMMENT             "Copying Python bindings"
    COMMAND             ${CMAKE_COMMAND} -E copy_if_different python/cprimes.py $<TARGET_FILE_DIR:cprimes>

    DEPENDS             python/cprimes.py
    WORKING_DIRECTORY   ${CMAKE_CURRENT_SOURCE_DIR}
)
