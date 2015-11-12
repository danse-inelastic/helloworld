# To improve
# * dependency items are declared at different places
#   - This file two places DEP_DANSE_PKGS, CPACK_DEBIAN_PACKAGE_DEPENDS
#   - File rpm.spec.in
# * rpm and deb releases are treated differently:
#   - rpm: source rpm
#   - deb: binary deb

cmake_minimum_required (VERSION 2.6)
project (helloworld)

set(VERSION "0.1")
set(AUTHOR "Jiao Lin")
set(AUTHOR_EMAILE "jiao.lin@gmail.com")
set(VENDOR "DANSE")
set(SUMMARY "helloworld: demonstration of a package with a c++ library, a python binding, and a python package.")
set(LICENSE "BSD")
set(RPM_APP_GROUP "Development/Tools")
set(GITHUB_URL "https://github.com/danse-inelastic/helloworld")

# variables
set (PYBINDING_NAME "${PROJECT_NAME}module")
set (LIB_NAME "${PROJECT_NAME}")
set (PKG_NAME "${PROJECT_NAME}")

# lib64
get_property(LIB64 GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS)
if ("${LIB64}" STREQUAL "TRUE")
    set(LIBSUFFIX 64)
else()
    set(LIBSUFFIX "")
endif()
set(INSTALL_LIB_DIR
  lib${LIBSUFFIX} CACHE PATH "Installation directory for libraries")
# message( STATUS "Install lib dir: ${INSTALL_LIB_DIR}")
mark_as_advanced(INSTALL_LIB_DIR)

#list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

# needs python
find_package ( PythonLibs REQUIRED )
find_package ( PythonInterp REQUIRED )
# python installation path
set(INSTALL_PY_PATH "${INSTALL_LIB_DIR}/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/site-packages")

#
enable_testing()

# subdirs
add_subdirectory(lib)
add_subdirectory(pyext)
add_subdirectory(python)
add_subdirectory(bin)
# add_subdirectory(etc)
add_subdirectory(tests)

# packaging
# CPACK
set(CPACK_PACKAGE_VERSION ${VERSION})
# set(CPACK_GENERATOR  "RPM")
set(CPACK_GENERATOR  "DEB")
set(CPACK_PACKAGE_NAME ${PKG_NAME})
set(CPACK_PACKAGE_SUMMARY ${SUMMARY})
set(CPACK_PACKAGE_LICENSE ${LICENSE})
set(CPACK_PACKAGE_RELEASE 0)
set(CPACK_PACKAGE_APP_GROUP ${RPM_APP_GROUP})
set(CPACK_PACKAGE_CONTACT ${AUTHOR})
set(CPACK_PACKAGE_VENDOR ${VENDOR})
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}")
set(CPACK_RPM_PACKAGE_REQUIRES "cmake")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "python, danse.ins")
include(CPack)

# source tar ball
add_custom_command(
  OUTPUT ${PKG_NAME}-${CPACK_PACKAGE_VERSION}.tar.gz
  COMMAND git archive --format=tar --prefix=${PKG_NAME}-${CPACK_PACKAGE_VERSION}/ HEAD | gzip -c > ${CMAKE_CURRENT_BINARY_DIR}/${PKG_NAME}-${CPACK_PACKAGE_VERSION}.tar.gz
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
add_custom_target( 
  src_tgz
  DEPENDS ${PKG_NAME}-${CPACK_PACKAGE_VERSION}.tar.gz 
  )

# CPack does not have a rule for source rpm
# the following is a way to do that
#
set(RPM_BUILD_DIR rpm_build)
# rpm spec file
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/rpm.spec.in
  ${CMAKE_CURRENT_BINARY_DIR}/${RPM_BUILD_DIR}/SPECS/${PKG_NAME}.spec )
# rules to build src rpm
set(SRC_RPM ${PKG_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.src.rpm)
add_custom_command(
  OUTPUT ${SRC_RPM}
  COMMAND ${CMAKE_COMMAND} -E make_directory ${RPM_BUILD_DIR}
  COMMAND ${CMAKE_COMMAND} -E make_directory ${RPM_BUILD_DIR}/BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory ${RPM_BUILD_DIR}/BUILDROOT
  COMMAND ${CMAKE_COMMAND} -E make_directory ${RPM_BUILD_DIR}/RPMS
  COMMAND ${CMAKE_COMMAND} -E make_directory ${RPM_BUILD_DIR}/SOURCES
  COMMAND ${CMAKE_COMMAND} -E make_directory ${RPM_BUILD_DIR}/SPECS
  COMMAND ${CMAKE_COMMAND} -E make_directory ${RPM_BUILD_DIR}/SRPMS
  COMMAND ${CMAKE_COMMAND} -E make_directory ${RPM_BUILD_DIR}/tmp
  COMMAND ${CMAKE_COMMAND} -E copy ${PKG_NAME}-${CPACK_PACKAGE_VERSION}.tar.gz ${RPM_BUILD_DIR}/SOURCES
  COMMAND rpmbuild -bs --define=\"_topdir ${RPM_BUILD_DIR}\" --buildroot=${RPM_BUILD_DIR}/tmp  ${RPM_BUILD_DIR}/SPECS/${PKG_NAME}.spec
  COMMAND ${CMAKE_COMMAND} -E copy ${RPM_BUILD_DIR}/SRPMS/${SRC_RPM} ${SRC_RPM}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  DEPENDS src_tgz
  )
add_custom_target( 
  srpm
  DEPENDS ${SRC_RPM}
  )

