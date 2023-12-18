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

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
  ${PROJECT_NAME} PRIVATE
  /Library/Frameworks/SDL2.framework/Versions/A/SDL2
  /Library/Frameworks/SDL2_image.framework/Versions/A/SDL2_image
  /Library/Frameworks/SDL2_ttf.framework/Versions/A/SDL2_ttf
)

target_include_directories(
  ${PROJECT_NAME} PRIVATE
  /Library/Frameworks/SDL2.framework/Versions/A/Headers
  /Library/Frameworks/SDL2_image.framework/Versions/A/Headers
  /Library/Frameworks/SDL2_ttf.framework/Versions/A/Headers
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

file(COPY graphics DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
