cmake_minimum_required(VERSION 3.20)
project(digit-ai VERSION 0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 6.0
    GIT_SHALLOW ON
)

FetchContent_MakeAvailable(raylib)

file(GLOB_RECURSE SOURCES
    "src/*.c"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
    include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    raylib
)

add_custom_command(
    TARGET digit-ai POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:digit-ai>/assets
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
        winmm
    )
endif()