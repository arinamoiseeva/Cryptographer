# CMake generated Testfile for 
# Source directory: C:/Users/arina/OneDrive/Desktop/cryptographer
# Build directory: C:/Users/arina/OneDrive/Desktop/cryptographer/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(SimpleNegative "C:/Users/arina/OneDrive/Desktop/cryptographer/build/run_tests.exe" "--gtest_filter=SimpleTest.Negative")
set_tests_properties(SimpleNegative PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/arina/OneDrive/Desktop/cryptographer/CMakeLists.txt;21;add_test;C:/Users/arina/OneDrive/Desktop/cryptographer/CMakeLists.txt;0;")
add_test(AffinePositive "C:/Users/arina/OneDrive/Desktop/cryptographer/build/run_tests.exe" "--gtest_filter=AffineTest.Positive")
set_tests_properties(AffinePositive PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/arina/OneDrive/Desktop/cryptographer/CMakeLists.txt;23;add_test;C:/Users/arina/OneDrive/Desktop/cryptographer/CMakeLists.txt;0;")
add_test(AffineNegative "C:/Users/arina/OneDrive/Desktop/cryptographer/build/run_tests.exe" "--gtest_filter=AffineTest.Negative")
set_tests_properties(AffineNegative PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/arina/OneDrive/Desktop/cryptographer/CMakeLists.txt;24;add_test;C:/Users/arina/OneDrive/Desktop/cryptographer/CMakeLists.txt;0;")
add_test(RecurrentPositive "C:/Users/arina/OneDrive/Desktop/cryptographer/build/run_tests.exe" "--gtest_filter=RecurrentAffineTest.Positive")
set_tests_properties(RecurrentPositive PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/arina/OneDrive/Desktop/cryptographer/CMakeLists.txt;26;add_test;C:/Users/arina/OneDrive/Desktop/cryptographer/CMakeLists.txt;0;")
add_test(RecurrentNegative "C:/Users/arina/OneDrive/Desktop/cryptographer/build/run_tests.exe" "--gtest_filter=RecurrentAffineTest.Negative")
set_tests_properties(RecurrentNegative PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/arina/OneDrive/Desktop/cryptographer/CMakeLists.txt;27;add_test;C:/Users/arina/OneDrive/Desktop/cryptographer/CMakeLists.txt;0;")
add_test(VigKeyPositive "C:/Users/arina/OneDrive/Desktop/cryptographer/build/run_tests.exe" "--gtest_filter=VigKeyTest.Positive")
set_tests_properties(VigKeyPositive PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/arina/OneDrive/Desktop/cryptographer/CMakeLists.txt;29;add_test;C:/Users/arina/OneDrive/Desktop/cryptographer/CMakeLists.txt;0;")
add_test(VigKeyNegative "C:/Users/arina/OneDrive/Desktop/cryptographer/build/run_tests.exe" "--gtest_filter=VigKeyTest.Negative")
set_tests_properties(VigKeyNegative PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/arina/OneDrive/Desktop/cryptographer/CMakeLists.txt;30;add_test;C:/Users/arina/OneDrive/Desktop/cryptographer/CMakeLists.txt;0;")
add_test(VigCipherPositive "C:/Users/arina/OneDrive/Desktop/cryptographer/build/run_tests.exe" "--gtest_filter=VigCipherTest.Positive")
set_tests_properties(VigCipherPositive PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/arina/OneDrive/Desktop/cryptographer/CMakeLists.txt;32;add_test;C:/Users/arina/OneDrive/Desktop/cryptographer/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
