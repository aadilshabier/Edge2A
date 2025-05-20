target_sources(${MAIN_LIB} PRIVATE
  graphdbio.cpp
  graph.cpp
  graphUtils.cpp
  graphdb.cpp
  graphdbTx.cpp
  matcher.cpp
)

target_include_directories(${MAIN_LIB} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# add_subdirectory(utils)
