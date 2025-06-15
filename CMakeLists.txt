cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(maev VERSION 0.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

find_package(Python REQUIRED COMPONENTS Development)

include(FetchContent)
FetchContent_Declare(SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 3.0.1
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(maev ${SRC_FILES})

target_compile_features(maev PRIVATE cxx_std_17)

target_include_directories(maev PUBLIC ${Python_INCLUDE_DIRS})
target_link_libraries(maev PRIVATE SFML::Graphics SFML::Audio ${Python_LIBRARIES})
