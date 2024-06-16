cmake_minimum_required(VERSION 3.20)

set(LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libraries/klangstrom-stm32") # set application and library paths
set(CMAKE_TOOLCHAIN_FILE "${LIBRARY_PATH}/arm-none-eabi-toolchain.cmake" CACHE STRING "Toolchain file") 

project(klangstrom-stm32-standalone)                                       # set project name

enable_language(C)
enable_language(CXX)
enable_language(ASM)

# Set C and C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

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

# Add custom command to create .bin file from .elf file
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.bin
    COMMENT "Converting .elf to .bin"
)
