cmake_minimum_required(VERSION 3.0.0)

SET(SRC_FILES 
    src/shader.cpp
    src/VBO.cpp
    src/VAO.cpp
    src/EBO.cpp
    src/window.cpp
    src/texture.cpp
    src/camera.cpp
    src/textureSet.cpp
    include/glObject.h
    )

add_library(glObjects STATIC ${SRC_FILES})

target_include_directories(glObjects PUBLIC ${PROJECT_SOURCE_DIR}/include include)
target_link_libraries(glObjects PUBLIC stb)
