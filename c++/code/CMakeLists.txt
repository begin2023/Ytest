cmake_minimum_required(3.12)
project(Ytest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)

include_directories(include)
add_subdirectory(main)
add_subdirectory(src)
add_subdirectory(test)