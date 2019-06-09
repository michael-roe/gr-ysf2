INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_YSF2 ysf2)

FIND_PATH(
    YSF2_INCLUDE_DIRS
    NAMES ysf2/api.h
    HINTS $ENV{YSF2_DIR}/include
        ${PC_YSF2_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    YSF2_LIBRARIES
    NAMES gnuradio-ysf2
    HINTS $ENV{YSF2_DIR}/lib
        ${PC_YSF2_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(YSF2 DEFAULT_MSG YSF2_LIBRARIES YSF2_INCLUDE_DIRS)
MARK_AS_ADVANCED(YSF2_LIBRARIES YSF2_INCLUDE_DIRS)

