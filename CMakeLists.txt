cmake_minimum_required(VERSION 3.20)

set(LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libraries/klangstrom-stm32")  # set application and library paths
include(${LIBRARY_PATH}/cmake/toolchain.cmake)                              # include `toolchain` before `project`
project(klangstrom-stm32-standalone)                                        # set project name

include(${LIBRARY_PATH}/cmake/pre.cmake)

# add executable

file(GLOB SOURCE_FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# add klangstrom-stm32

add_subdirectory(${LIBRARY_PATH})
target_link_libraries(${PROJECT_NAME} PRIVATE klangstrom-stm32)

include(${LIBRARY_PATH}/cmake/post.cmake)
