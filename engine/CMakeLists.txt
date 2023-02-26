
find_package(SDL2 REQUIRED)
find_package(OpenImageIO CONFIG REQUIRED)

file(GLOB_RECURSE srcfiles "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

add_library(engine "${srcfiles}")

target_include_directories(engine PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
target_link_libraries(engine PUBLIC ${SDL2_LIBRARIES})
target_link_libraries(engine PUBLIC OpenImageIO::OpenImageIO)
target_link_libraries(engine PUBLIC ImGui ${CMAKE_DL_LIBS})
target_link_libraries(engine PUBLIC -lGL)
target_link_libraries(engine PUBLIC -lGLEW)