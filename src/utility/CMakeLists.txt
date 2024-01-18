cmake_minimum_required(VERSION 3.0.0)

SET(UTILITY_SRC
    src/light.cpp
    src/model.cpp
    src/worldObject.cpp
    )

add_library(utility STATIC ${UTILITY_SRC})

target_include_directories(utility PUBLIC ${PROJECT_SOURCE_DIR}/include include ${PROJECT_SOURCE_DIR}/src/glObjects/include)

