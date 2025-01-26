set(TEST_NAME edge2a_test)

add_executable(${TEST_NAME} TestA.cpp)
target_link_libraries(${TEST_NAME} PRIVATE gtest gtest_main ${MAIN_LIB})

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
