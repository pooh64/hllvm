cmake_minimum_required(VERSION 3.10)

add_library(libuvideomem SHARED
    uvideomem.cpp
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
set_target_properties(libuvideomem PROPERTIES AUTOMOC TRUE)
target_link_libraries(libuvideomem Qt5::Widgets)
target_include_directories(libuvideomem PRIVATE "${PROJECT_SOURCE_DIR}")