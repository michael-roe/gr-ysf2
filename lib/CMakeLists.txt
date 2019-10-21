# Copyright 2011,2012,2016 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

list(APPEND ysf2_sources
    fich_parser_b_impl.cc
    vech_decode_bb_impl.cc
    vech_decode_fb_impl.cc
    vech_encode_bb_impl.cc
    fich_source_b_impl.cc
    dch_parser_b_impl.cc
    vocoder_dummy_bf_impl.cc
    dch_source_b_impl.cc
    dch_errors_bb_impl.cc
)

set(ysf2_sources "${ysf2_sources}" PARENT_SCOPE)
if(NOT ysf2_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT ysf2_sources)

add_library(gnuradio-ysf2 SHARED ${ysf2_sources})
target_link_libraries(gnuradio-ysf2 ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES})
set_target_properties(gnuradio-ysf2 PROPERTIES DEFINE_SYMBOL "gnuradio_ysf2_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-ysf2 PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
include(GrMiscUtils)
GR_LIBRARY_FOO(gnuradio-ysf2 RUNTIME_COMPONENT "ysf2_runtime" DEVEL_COMPONENT "ysf2_devel")

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})

list(APPEND test_ysf2_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_ysf2.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_ysf2.cc
)

add_executable(test-ysf2 ${test_ysf2_sources})

target_link_libraries(
  test-ysf2
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-ysf2
)

GR_ADD_TEST(test_ysf2 test-ysf2)

########################################################################
# Print summary
########################################################################
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building for version: ${VERSION} / ${LIBVER}")

