cmake_minimum_required(VERSION 3.10)

add_executable(upt
    upt.c
    shapes.c
    surfaces.c
)

target_include_directories(upt PUBLIC "${PROJECT_SOURCE_DIR}")
target_link_libraries(upt libuvideomem m)
install(TARGETS upt DESTINATION ${HLLVM_INSTALL_BIN_DIR})