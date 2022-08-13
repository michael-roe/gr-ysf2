/* -*- c++ -*- */
/*
 * Copyright 2022 Michael Roe.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_YSF2_FICH_PARSER_B_IMPL_H
#define INCLUDED_YSF2_FICH_PARSER_B_IMPL_H

#include <gnuradio/ysf2/fich_parser_b.h>

namespace gr {
namespace ysf2 {

class fich_parser_b_impl : public fich_parser_b {
private:
  pmt::pmt_t d_port;

public:
  fich_parser_b_impl();
  ~fich_parser_b_impl();

  // Where all the action really happens
  int work(int noutput_items, gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
};

} // namespace ysf2
} // namespace gr

#endif /* INCLUDED_YSF2_FICH_PARSER_B_IMPL_H */
