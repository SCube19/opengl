cmake_minimum_required(VERSION 3.0.0)

SET(UTILITY_SRC
    src/VAOFactory.cpp
    )

add_library(utility STATIC ${UTILITY_SRC})

add_library(shapes STATIC ${PROJECT_SOURCE_DIR}/include/predefined/shapes.cpp)

target_include_directories(utility PUBLIC ${PROJECT_SOURCE_DIR}/include include ${PROJECT_SOURCE_DIR}/src/glObjects/include)
target_link_libraries(utility PUBLIC shapes)