cmake_minimum_required(VERSION 3.0.0)
project(cloudRenderer VERSION 0.1.0)

find_package(SDL2 REQUIRED)

add_executable(cloudRenderer src/main.cpp src/engine.cpp src/engine.h src/inputmanager.h src/inputmanager.cpp)
target_include_directories(cloudRenderer PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(cloudRenderer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
target_link_libraries(cloudRenderer PRIVATE ${SDL2_LIBRARIES})