cmake_minimum_required(VERSION 3.29)

set(KLST_STM32_LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libraries/klangstrom-stm32")   # set application and library paths
set(KLST_LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libraries/klangstrom-libraries")
include(${KLST_STM32_LIBRARY_PATH}/cmake/toolchain.cmake)                               # include `toolchain` before `project`
project(klangstrom-stm32-standalone)                                                    # set project name
set(KLST_ENV 0x36)                                                                      # set KLST environment
                                                                                        #     0x36=KLST_PANDA_STM32
                                                                                        #     0x37=KLST_CATERPILLAR_STM32

# add pre

include(${KLST_STM32_LIBRARY_PATH}/cmake/pre.cmake)

# add executable

file(GLOB SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
# add klangstrom-stm32

add_subdirectory(${KLST_STM32_LIBRARY_PATH})
add_subdirectory(${KLST_LIBRARY_PATH}/Klangstrom)
add_subdirectory(${KLST_LIBRARY_PATH}/Klangstrom_KLST_PANDA_STM32)

# propagate include directories and compile definitions from klangstrom-stm32 + Klangstrom_KLST_PANDA_STM32 to klangstrom

get_target_property(KLANGSTROM_STM32_INCLUDE_DIRS klangstrom-stm32 INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(KLANGSTROM_STM32_COMPILE_DEFINITIONS klangstrom-stm32 INTERFACE_COMPILE_DEFINITIONS)
target_include_directories(klangstrom PUBLIC ${KLANGSTROM_STM32_INCLUDE_DIRS})
target_compile_definitions(klangstrom PUBLIC ${KLANGSTROM_STM32_COMPILE_DEFINITIONS})

get_target_property(KLANGSTROM_KLST_PANDA_STM32_INCLUDE_DIRS Klangstrom_KLST_PANDA_STM32 INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(klangstrom PUBLIC ${KLANGSTROM_KLST_PANDA_STM32_INCLUDE_DIRS})

# add executable

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE klangstrom-stm32 klangstrom Klangstrom_KLST_PANDA_STM32)

# add post

include(${KLST_STM32_LIBRARY_PATH}/cmake/post.cmake)
