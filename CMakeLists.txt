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

include_directories(inc src/glObjects/include)

add_subdirectory(src)
add_subdirectory(src/glObjects)

add_executable(real_engine src/main.cpp)

target_link_libraries(real_engine glad glfw glObjects)

configure_file(src/shaders/default.vert shaders/default.vert COPYONLY)
configure_file(src/shaders/default.frag shaders/default.frag COPYONLY)

find_package(OpenGL REQUIRED)

# include_directories(include)

# file(GLOB SOURCES "src/*.cpp" "src/*.c")

# add_executable(opengl ${SOURCES})

# target_link_libraries(opengl glfw)



