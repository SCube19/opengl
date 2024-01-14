cmake_minimum_required(VERSION 3.0.0)

SET(SRC_FILES 
    src/shader.cpp
    src/VBO.cpp
    src/VAO.cpp
    src/EBO.cpp
    include/glObject.h
    )

#for static libraries
add_library(glObjects STATIC ${SRC_FILES})

target_include_directories(glObjects PUBLIC ${PROJECT_SOURCE_DIR}/include include)

