cmake_minimum_required(VERSION 3.22)
include(FetchContent)

project(edge2a LANGUAGES CXX)
set(MAIN_LIB edge2a_core)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_REQUIRED ON)

# Fetch JSON library
FetchContent_Declare(json
  DOWNLOAD_EXTRACT_TIMESTAMP OFF
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

# Fetch GoogleTest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Library for core functionality
add_library(${MAIN_LIB})
add_subdirectory(src)
target_link_libraries(${MAIN_LIB} PRIVATE nlohmann_json::nlohmann_json)
# TODO: set public include directory for ${MAIN_LIB}

# Main executable
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${MAIN_LIB})

# Enable testing and add tests directory
enable_testing()
add_subdirectory(tests)
