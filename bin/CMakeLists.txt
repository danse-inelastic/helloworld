#
configure_file(hello.py hello.py)
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/hello.py DESTINATION bin)
