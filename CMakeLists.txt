cmake_minimum_required(VERSION 3.22)
include(FetchContent)

project(edge2a LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_REQUIRED ON)

FetchContent_Declare(json
  DOWNLOAD_EXTRACT_TIMESTAMP OFF
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)


add_executable(${PROJECT_NAME})
add_subdirectory(src)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
