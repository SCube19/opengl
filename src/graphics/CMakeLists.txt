cmake_minimum_required(VERSION 3.0.0)

SET(GRAPHICS_SRC
    src/light.cpp
    src/model.cpp
    src/worldObject.cpp
    src/lightManager.cpp
    src/mesh.cpp
    )

add_library(graphics STATIC ${GRAPHICS_SRC})

target_include_directories(graphics PUBLIC 
${PROJECT_SOURCE_DIR}/include 
include 
${PROJECT_SOURCE_DIR}/src/glObjects/include
${PROJECT_SOURCE_DIR}/src/utility/include)
target_link_libraries(graphics PUBLIC glObjects)
