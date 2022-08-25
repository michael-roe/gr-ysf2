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
  std::vector<uint8_t> bytes = pmt::u8vector_elements(pmt::cdr(msg));
  pmt::pmt_t dict;
  pmt::pmt_t dict_in;
  pmt::pmt_t value;
  int frame_number;

  dict_in = pmt::car(msg);
  if (!pmt::is_dict(dict_in))
  {
    message_port_pub(d_port_out, pmt::PMT_F);
  }
  else if (bytes.size() < 4)
  {
    message_port_pub(d_port_out, pmt::PMT_F);
  }
  else
  {
    frame_number = (bytes[1] >> 3) & 0x7;

    dict = pmt::make_dict();
    dict = pmt::dict_add(dict, pmt::intern("payload_len"),
      pmt::from_long(360));
    dict = pmt::dict_add(dict, pmt::intern("frame_number"),
      pmt::from_long(frame_number));
    value = pmt::dict_ref(dict_in, d_rx_time_key, pmt::PMT_NIL);
    if (!pmt::is_null(value))
      dict = pmt::dict_add(dict, d_rx_time_key, value);
    message_port_pub(d_port_out, dict);
  }
}

void async_fich_parser_impl::crc_notok(pmt::pmt_t msg)
{
  message_port_pub(d_port_out, pmt::PMT_F);
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
  d_rx_time_key = pmt::intern("rx_time");
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
