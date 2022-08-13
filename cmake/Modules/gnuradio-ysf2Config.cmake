find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_YSF2 gnuradio-ysf2)

FIND_PATH(
    GR_YSF2_INCLUDE_DIRS
    NAMES gnuradio/ysf2/api.h
    HINTS $ENV{YSF2_DIR}/include
        ${PC_YSF2_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_YSF2_LIBRARIES
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

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-ysf2Target.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_YSF2 DEFAULT_MSG GR_YSF2_LIBRARIES GR_YSF2_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_YSF2_LIBRARIES GR_YSF2_INCLUDE_DIRS)
