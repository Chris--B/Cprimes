
file(COPY
	run-all-tests.bat
	DESTINATION ${BIN_DIR}/)


add_subdirectory(c)
add_subdirectory(python)
