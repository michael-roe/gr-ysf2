# Copyright 2011 Free Software Foundation, Inc.
#
# This file was generated by gr_modtool, a tool from the GNU Radio framework
# This file is a part of gr-ysf2
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

install(FILES
    ysf2_fich_source_b.block.yml
    ysf2_fich_parser_b.block.yml
    ysf2_dch_errors_bb.block.yml
    ysf2_dch_parser_b.block.yml
    ysf2_dch_source_b.block.yml
    ysf2_vech_decode_bb.block.yml
    ysf2_vech_decode_fb.block.yml
    ysf2_vech_encode_bb.block.yml
    ysf2_vocoder_dummy_bf.block.yml DESTINATION share/gnuradio/grc/blocks
)
