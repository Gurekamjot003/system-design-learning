cmake_minimum_required(VERSION 3.10)

project(DatingAppTinder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include headers
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Chat
    ${CMAKE_SOURCE_DIR}/Core
    ${CMAKE_SOURCE_DIR}/Location
    ${CMAKE_SOURCE_DIR}/Notification
    ${CMAKE_SOURCE_DIR}/User
    ${CMAKE_SOURCE_DIR}/enumerations
)

# Gather all source files (excluding build system generated files)
file(GLOB_RECURSE SRC_FILES
    ${CMAKE_SOURCE_DIR}/Chat/*.cpp
    ${CMAKE_SOURCE_DIR}/Core/*.cpp
    ${CMAKE_SOURCE_DIR}/Location/*.cpp
    ${CMAKE_SOURCE_DIR}/Notification/*.cpp
    ${CMAKE_SOURCE_DIR}/User/*.cpp
)

# Add main separately
add_executable(DatingApp main.cpp ${SRC_FILES})
