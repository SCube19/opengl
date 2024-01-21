cmake_minimum_required(VERSION 3.0.0)
project(opengl VERSION 0.1.0 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CPack)

include_directories(inc src/glObjects/include src/utility/include src/graphics/include src/static)

add_subdirectory(src)
add_subdirectory(src/glObjects)
add_subdirectory(src/utility)
add_subdirectory(src/graphics)

add_executable(real_engine src/main.cpp)

target_link_libraries(real_engine glad stb glfw glObjects utility graphics assimp)

file(COPY shaders DESTINATION .)
file(COPY textures DESTINATION .)
file(COPY models DESTINATION .)

find_package(OpenGL REQUIRED)




