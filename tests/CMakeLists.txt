add_executable(TestIO TestIO.cpp)
target_link_libraries(TestIO
  PRIVATE GTest::gtest_main ${MAIN_LIB} nlohmann_json::nlohmann_json)
target_include_directories(TestIO PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)

add_executable(TestParsing TestParsing.cpp)
target_link_libraries(TestParsing
  PRIVATE GTest::gtest_main ${MAIN_LIB})
target_include_directories(TestParsing PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)

add_executable(TestMatching TestMatching.cpp)
target_link_libraries(TestMatching
  PRIVATE GTest::gtest_main ${MAIN_LIB})
target_include_directories(TestMatching PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)

add_executable(TestMatchingVF2 TestMatchingVF2.cpp)
target_link_libraries(TestMatchingVF2
  PRIVATE GTest::gtest_main ${MAIN_LIB})
target_include_directories(TestMatchingVF2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)

include(GoogleTest)
gtest_discover_tests(TestIO)
gtest_discover_tests(TestParsing)
gtest_discover_tests(TestMatching)
gtest_discover_tests(TestMatchingVF2)
