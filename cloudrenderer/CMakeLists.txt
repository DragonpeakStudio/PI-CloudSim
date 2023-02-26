file(GLOB_RECURSE srcfiles "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

add_executable(cloudRenderer "${srcfiles}")
target_link_libraries(cloudRenderer PRIVATE engine)
add_custom_command(TARGET cloudRenderer POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/../resources $<TARGET_FILE_DIR:cloudRenderer>/../resources)