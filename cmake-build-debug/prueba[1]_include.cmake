if(EXISTS "/home/moko/Escritorio/jazzjackrabbit_taller1/cmake-build-debug/prueba[1]_tests.cmake")
  include("/home/moko/Escritorio/jazzjackrabbit_taller1/cmake-build-debug/prueba[1]_tests.cmake")
else()
  add_test(prueba_NOT_BUILT prueba_NOT_BUILT)
endif()