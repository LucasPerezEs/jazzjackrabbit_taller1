if(EXISTS "/home/moko/Escritorio/jazzjackrabbit_taller1/cmake-build-debug/test_src/YourProjectName_test[1]_tests.cmake")
  include("/home/moko/Escritorio/jazzjackrabbit_taller1/cmake-build-debug/test_src/YourProjectName_test[1]_tests.cmake")
else()
  add_test(YourProjectName_test_NOT_BUILT YourProjectName_test_NOT_BUILT)
endif()
