cmake_minimum_required(VERSION 3.0.0)
project(cloudRenderer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

add_executable(cloudRenderer src/main.cpp src/engine.cpp src/engine.h src/inputmanager.h src/inputmanager.cpp src/renderer.cpp src/renderer.h src/window.h src/window.cpp )
target_include_directories(cloudRenderer PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(cloudRenderer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
target_link_libraries(cloudRenderer PRIVATE ${SDL2_LIBRARIES})
target_link_libraries(cloudRenderer PRIVATE -lGL)
target_link_libraries(cloudRenderer PRIVATE -lGLEW)
add_custom_command(TARGET cloudRenderer POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:cloudRenderer>/resources)