find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

FLEX_TARGET(Lexer lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cpp)
BISON_TARGET(Parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cpp COMPILE_FLAGS -d)
ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

add_library(${PARSER_LIB}
  parser.cpp
  parser.tab.hpp
  ../graphdb.cpp 
  ${BISON_Parser_OUTPUTS}
  ${FLEX_Lexer_OUTPUTS}
)

target_compile_options(${PARSER_LIB} PRIVATE -w) # Silence warnings
target_include_directories(${PARSER_LIB} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
