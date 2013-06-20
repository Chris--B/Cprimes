
add_custom_target(copy_bindings
	ALL
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/python/cprimes.py
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/python/cprimes.py ${BIN_DIR})

