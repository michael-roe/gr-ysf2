# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

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
    python_bindings.cc)

GR_PYBIND_MAKE_OOT(ysf2 
   ../..
   gr::ysf2
   "${ysf2_python_files}")

install(TARGETS ysf2_python DESTINATION ${GR_PYTHON_DIR}/ysf2 COMPONENT pythonapi)
