target_sources(${PROJECT_NAME} PRIVATE
  graphdbio.cpp
  graph.cpp
  graphdb.cpp
  main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# add_subdirectory(utils)
