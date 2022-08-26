# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT ysf2_sources)
    MESSAGE(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT ysf2_sources)

########################################################################
# Check for pygccxml
########################################################################
GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND ysf2_python_files
    fich_parser_b_python.cc
    async_fich_parser_python.cc
    async_dch_parser_python.cc
    fich_source_b_python.cc python_bindings.cc)

GR_PYBIND_MAKE_OOT(ysf2
   ../../..
   gr::ysf2
   "${ysf2_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(TARGET ysf2_python POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ysf2_python>
    ${PROJECT_BINARY_DIR}/test_modules/gnuradio/ysf2/
)

install(TARGETS ysf2_python DESTINATION ${GR_PYTHON_DIR}/gnuradio/ysf2 COMPONENT pythonapi)
