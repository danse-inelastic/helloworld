# ------------- Modify these -------------
set ( SRC_FILES 
  hello.cc
  )

set ( INC_FILES
  hello.h
  )

set ( EXPORT_HEADERS ${INC_FILES} )
# ----------------------------------------

# include python headers, if necessary
# include_directories( ${PYTHON_INCLUDE_DIRS} )

# export headers from this project
foreach (header ${EXPORT_HEADERS})
  configure_file(
    "${header}"
    "${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/${header}"
    )
endforeach (header)

# -I and -L
include_directories(${CMAKE_BINARY_DIR}/lib/include)
# compile shared lib
add_library ( ${LIB_NAME} SHARED ${SRC_FILES} ${INC_FILES} )

# install headers
install (
  DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME})
# install shared lib
install (TARGETS ${LIB_NAME}
  LIBRARY DESTINATION ${INSTALL_LIB_DIR}
  )
