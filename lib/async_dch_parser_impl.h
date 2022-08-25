/* -*- c++ -*- */
/*
 * Copyright 2022 Michael Roe.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_YSF2_ASYNC_DCH_PARSER_IMPL_H
#define INCLUDED_YSF2_ASYNC_DCH_PARSER_IMPL_H

#include <gnuradio/ysf2/async_dch_parser.h>

namespace gr {
namespace ysf2 {

class async_dch_parser_impl : public async_dch_parser {
private:
  pmt::pmt_t d_port_in;
  pmt::pmt_t d_port_callsign;
  pmt::pmt_t d_port_location;

  void message(pmt::pmt_t msg);

public:
  async_dch_parser_impl();
  ~async_dch_parser_impl();

  // Where all the action really happens
  int work(int noutput_items, gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
};

} // namespace ysf2
} // namespace gr

#endif /* INCLUDED_YSF2_ASYNC_DCH_PARSER_IMPL_H */
