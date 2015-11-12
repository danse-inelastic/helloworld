add_test(NAME test-py
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test.py
  )
add_test(NAME test-bin
  COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test.sh
  )
set_tests_properties(test-py test-bin
  PROPERTIES ENVIRONMENT "PYTHONPATH=${CMAKE_BINARY_DIR}/python/modules;LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/lib;PATH=${CMAKE_BINARY_DIR}/bin:$ENV{PATH}"
  )
