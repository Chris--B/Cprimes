
add_executable(
	benchmark-eratos
	c/eratos.cpp
)

target_link_libraries(benchmark-eratos ${CELERO} ${CPRIMESLIB})