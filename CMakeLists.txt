cmake_minimum_required(VERSION 3.10)
project(FiestaCalculator)

set(CMAKE_CXX_STANDARD 17)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/data)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/exports)

add_executable(fiesta_calculator
    src/main.cpp
    src/GUI.h
    src/Calculator.h
    src/Database.h
)

add_executable(tests
  tests/CalculatorTest.cpp
  tests/DatabaseTest.cpp
  src/Calculator.h
  src/Database.h
)

target_include_directories(fiesta_calculator PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(fiesta_calculator ${GTKMM_LIBRARIES} sqlite3)
target_include_directories(tests PRIVATE
  ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(tests
  GTest::gtest_main
  sqlite3
)

enable_testing()
add_test(NAME AllTests COMMAND tests)