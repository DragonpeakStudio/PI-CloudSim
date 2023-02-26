cmake_minimum_required(VERSION 3.0.0)
project(cloudRenderer VERSION 0.1.0)

add_compile_options(-Wall -Wextra -Wpedantic)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(imgui)

add_subdirectory(engine)
add_subdirectory(cloudrenderer)

