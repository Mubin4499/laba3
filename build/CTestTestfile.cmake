# CMake generated Testfile for 
# Source directory: C:/fiesta_calculator
# Build directory: C:/fiesta_calculator/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(AllTests "C:/fiesta_calculator/build/tests.exe")
set_tests_properties(AllTests PROPERTIES  _BACKTRACE_TRIPLES "C:/fiesta_calculator/CMakeLists.txt;44;add_test;C:/fiesta_calculator/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
