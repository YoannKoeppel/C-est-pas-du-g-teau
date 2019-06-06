# Requirement
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 14)

# ---------------------------------------- PROJECT FILES
project(imac-tower-defense)
file(
    GLOB_RECURSE 
    MY_SOURCES 
    src/*
)

# ---------------------------------------- FIND DEPENDENCIES
# Common on all platform
find_package(OpenGL REQUIRED)
if (WIN32) # On windows
    set(SDL2_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/lib/SDL2-2.0.9/include)
    set(SDL2_LIBRARIES ${CMAKE_SOURCE_DIR}/lib/SDL2-2.0.9/lib/windows_x86/SDL2.lib;${CMAKE_SOURCE_DIR}/lib/SDL2-2.0.9/lib/windows_x86/SDL2main.lib)
else() # On linux
    find_package(SDL2 REQUIRED)
endif()

# ----------------------------------------- BUILD DEPENDENCIES IF NEEDED
add_library(STB_IMAGE STATIC "lib/stb_image/stb_image.cpp")
add_library(GLAD STATIC "lib/glad/src/glad.c")

# ----------------------------------------- INCLUDE DIRECTORIES
include_directories(
    ${OPENGL_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIRS}
    lib/glad/include
    lib
    src
)

# ------------------------------------------- BUILD PROJECT
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
add_executable(${PROJECT_NAME} ${MY_SOURCES})
target_link_libraries(
    ${PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    ${SDL2_LIBRARIES}
    STB_IMAGE
    GLAD
)

if (UNIX) # Use dynamic linking library
    target_link_libraries(${PROJECT_NAME} -ldl)
endif()

if (WIN32) # Copy .dll to build folder
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/lib/SDL2-2.0.9/lib/windows_x86/SDL2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()

