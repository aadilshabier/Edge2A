set(TEST_NAME edge2a_test)

add_executable(${TEST_NAME} TestA.cpp)
target_link_libraries(${TEST_NAME} PRIVATE gtest gtest_main ${MAIN_LIB} nlohmann_json::nlohmann_json)
target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
