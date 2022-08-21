/* -*- c++ -*- */
/*
 * Copyright 2022 Michael Roe.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_YSF2_ASYNC_FICH_PARSER_IMPL_H
#define INCLUDED_YSF2_ASYNC_FICH_PARSER_IMPL_H

#include <gnuradio/ysf2/async_fich_parser.h>

namespace gr {
namespace ysf2 {

class async_fich_parser_impl : public async_fich_parser {
private:
  pmt::pmt_t d_port_ok;
  pmt::pmt_t d_port_notok;
  pmt::pmt_t d_port_out;

  void crc_ok(pmt::pmt_t msg);
  void crc_notok(pmt::pmt_t msg);

public:
  async_fich_parser_impl();
  ~async_fich_parser_impl();

  // Where all the action really happens
  int work(int noutput_items, gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
};

} // namespace ysf2
} // namespace gr

#endif /* INCLUDED_YSF2_ASYNC_FICH_PARSER_IMPL_H */
