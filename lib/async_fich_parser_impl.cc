/* -*- c++ -*- */
/*
 * Copyright 2022 Michael Roe.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "async_fich_parser_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace ysf2 {

async_fich_parser::sptr async_fich_parser::make() {
  return gnuradio::make_block_sptr<async_fich_parser_impl>();
}

void async_fich_parser_impl::crc_ok(pmt::pmt_t msg)
{
  printf("crc ok\n");
}

void async_fich_parser_impl::crc_notok(pmt::pmt_t msg)
{
  printf("crc notok\n");
}

/*
 * The private constructor
 */
async_fich_parser_impl::async_fich_parser_impl()
    : gr::sync_block(
          "async_fich_parser",
          gr::io_signature::make(0, 0, 0),
          gr::io_signature::make(0, 0, 0))
{
  d_port_ok = pmt::mp("ok");
  d_port_notok = pmt::mp("notok");
  d_port_out = pmt::mp("out");
  message_port_register_in(d_port_ok);
  message_port_register_in(d_port_notok);
  message_port_register_out(d_port_out);
  set_msg_handler(d_port_ok,
    [this](pmt::pmt_t msg) { this->crc_ok(msg); });
  set_msg_handler(d_port_notok,
    [this](pmt::pmt_t msg) { this->crc_notok(msg); });
}

/*
 * Our virtual destructor.
 */
async_fich_parser_impl::~async_fich_parser_impl() {}

int async_fich_parser_impl::work(int noutput_items,
                                 gr_vector_const_void_star &input_items,
                                 gr_vector_void_star &output_items) {

  // Do <+signal processing+>

  // Tell runtime system how many output items we produced.
  return noutput_items;
}

} /* namespace ysf2 */
} /* namespace gr */
