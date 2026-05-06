set(CALC_LIB_SOURCES
    ${CMAKE_SOURCE_DIR}/src/parser.cpp
    ${CMAKE_SOURCE_DIR}/src/calc.cpp
)

add_executable(calculator_tests
    ${CALC_LIB_SOURCES}
    parser_test.cpp
    calc_test.cpp
)

target_include_directories(calculator_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${math_SOURCE_DIR}/include
)

target_link_libraries(calculator_tests PRIVATE
    GTest::gtest_main
    nlohmann_json::nlohmann_json
)

include(GoogleTest)
gtest_discover_tests(calculator_tests)