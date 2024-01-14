cmake_minimum_required(VERSION 3.0.0)

SET(SRC_FILES 
    glad.c
    )

#for static libraries
add_library(glad STATIC ${SRC_FILES})

target_include_directories(glad PUBLIC ${PROJECT_SOURCE_DIR}/include)

