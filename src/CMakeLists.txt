target_sources(${MAIN_LIB} PRIVATE
  graphdbio.cpp
  graphdb.cpp
)

target_include_directories(${MAIN_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# add_subdirectory(utils)
