# CMake generated Testfile for 
# Source directory: C:/Users/matve/Desktop/Task_1
# Build directory: C:/Users/matve/Desktop/Task_1/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(user_group_manager_test "C:/Users/matve/Desktop/Task_1/build/Debug/user_group_manager.exe")
  set_tests_properties(user_group_manager_test PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/matve/Desktop/Task_1/CMakeLists.txt;55;add_test;C:/Users/matve/Desktop/Task_1/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(user_group_manager_test "C:/Users/matve/Desktop/Task_1/build/Release/user_group_manager.exe")
  set_tests_properties(user_group_manager_test PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/matve/Desktop/Task_1/CMakeLists.txt;55;add_test;C:/Users/matve/Desktop/Task_1/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(user_group_manager_test "C:/Users/matve/Desktop/Task_1/build/MinSizeRel/user_group_manager.exe")
  set_tests_properties(user_group_manager_test PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/matve/Desktop/Task_1/CMakeLists.txt;55;add_test;C:/Users/matve/Desktop/Task_1/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(user_group_manager_test "C:/Users/matve/Desktop/Task_1/build/RelWithDebInfo/user_group_manager.exe")
  set_tests_properties(user_group_manager_test PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/matve/Desktop/Task_1/CMakeLists.txt;55;add_test;C:/Users/matve/Desktop/Task_1/CMakeLists.txt;0;")
else()
  add_test(user_group_manager_test NOT_AVAILABLE)
endif()
