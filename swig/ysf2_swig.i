/* -*- c++ -*- */

#define YSF2_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "ysf2_swig_doc.i"

%{
#include "ysf2/fich_parser_b.h"
#include "ysf2/vech_decode_bb.h"
#include "ysf2/vech_decode_fb.h"
%}


%include "ysf2/fich_parser_b.h"
GR_SWIG_BLOCK_MAGIC2(ysf2, fich_parser_b);
%include "ysf2/vech_decode_bb.h"
GR_SWIG_BLOCK_MAGIC2(ysf2, vech_decode_bb);
%include "ysf2/vech_decode_fb.h"
GR_SWIG_BLOCK_MAGIC2(ysf2, vech_decode_fb);
