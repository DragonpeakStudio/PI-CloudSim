cmake_minimum_required(VERSION 3.0.0)
project(cloudRenderer VERSION 0.1.0)

add_compile_options(-Wall -Wextra -Wpedantic)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
file(GLOB_RECURSE srcfiles "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
find_package(SDL2 REQUIRED)
find_package(OpenImageIO CONFIG REQUIRED)

add_subdirectory(imgui)

add_executable(cloudRenderer "${srcfiles}")
target_include_directories(cloudRenderer PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(cloudRenderer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
target_link_libraries(cloudRenderer PRIVATE ${SDL2_LIBRARIES})
target_link_libraries(cloudRenderer PRIVATE OpenImageIO::OpenImageIO)
target_link_libraries(cloudRenderer PUBLIC ImGui ${CMAKE_DL_LIBS})
target_link_libraries(cloudRenderer PRIVATE -lGL)
target_link_libraries(cloudRenderer PRIVATE -lGLEW)
add_custom_command(TARGET cloudRenderer POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:cloudRenderer>/resources)