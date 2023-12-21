cmake_minimum_required(VERSION 3.5.0)
project(flappy-bird VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(SOURCES
   src/main.cpp
   src/bird.cpp
   src/game.cpp
   src/pipe.cpp
)

find_package(SDL2 REQUIRED COMPONENTS SDL2)
find_package(SDL2_image REQUIRED COMPONENTS SDL2_image)
find_package(SDL2_ttf REQUIRED COMPONENTS SDL2_ttf)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image::SDL2_image)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_ttf::SDL2_ttf)

target_include_directories(${PROJECT_NAME} PRIVATE include)

file(COPY graphics DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
