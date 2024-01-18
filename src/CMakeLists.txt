cmake_minimum_required(VERSION 3.0.0)

SET(GLAD_FILES glad.c)

SET(STB_FILES stb_image.cpp)

#for static libraries
add_library(glad STATIC ${GLAD_FILES})

add_library(stb STATIC ${STB_FILES})

target_include_directories(glad PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(stb PUBLIC ${PROJECT_SOURCE_DIR}/include)
