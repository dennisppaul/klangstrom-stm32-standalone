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

# add klangstrom-stm32, klangstrom, Klangstrom_KLST_PANDA_STM32

add_subdirectory(${KLST_STM32_LIBRARY_PATH})
add_subdirectory(${KLST_LIBRARY_PATH}/Klangstrom)
add_subdirectory(${KLST_LIBRARY_PATH}/Klangstrom_KLST_PANDA_STM32)

# propagate KLST_ENV

target_compile_definitions(klangstrom PUBLIC KLST_ENV=${KLST_ENV})
target_compile_definitions(klangstrom-stm32 PUBLIC KLST_ENV=${KLST_ENV})
target_compile_definitions(Klangstrom_KLST_PANDA_STM32 PUBLIC KLST_ENV=${KLST_ENV})

# propagate include directories

get_target_property(KLANGSTROM_INCLUDE_DIRS klangstrom INTERFACE_INCLUDE_DIRECTORIES) # for `KlangstromEnvironment.h`
get_target_property(KLANGSTROM_STM32_INCLUDE_DIRS klangstrom-stm32 INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(KLANGSTROM_KLST_PANDA_STM32_INCLUDE_DIRS Klangstrom_KLST_PANDA_STM32 INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(klangstrom PUBLIC ${KLANGSTROM_STM32_INCLUDE_DIRS})
target_include_directories(klangstrom PUBLIC ${KLANGSTROM_KLST_PANDA_STM32_INCLUDE_DIRS})
target_include_directories(klangstrom-stm32 PUBLIC ${KLANGSTROM_INCLUDE_DIRS})

# propagate compile definitions

get_target_property(KLANGSTROM_STM32_COMPILE_DEFINITIONS klangstrom-stm32 INTERFACE_COMPILE_DEFINITIONS)
target_compile_definitions(klangstrom PUBLIC ${KLANGSTROM_STM32_COMPILE_DEFINITIONS})
target_compile_definitions(Klangstrom_KLST_PANDA_STM32 PUBLIC ${KLANGSTROM_STM32_COMPILE_DEFINITIONS})

# add executable

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${KLANGSTROM_STM32_COMPILE_DEFINITIONS})
target_link_libraries(${PROJECT_NAME} PRIVATE
        klangstrom
        Klangstrom_KLST_PANDA_STM32
        klangstrom-stm32
)

# add post

include(${KLST_STM32_LIBRARY_PATH}/cmake/post.cmake)
