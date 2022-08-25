/* -*- c++ -*- */
/*
 * Copyright 2022 Michael Roe.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "async_dch_parser_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace ysf2 {

async_dch_parser::sptr async_dch_parser::make() {
  return gnuradio::make_block_sptr<async_dch_parser_impl>();
}

static const unsigned char scramble[] = {0x93, 0xd7, 0x51, 0x21, 0x9c, 0x2f, 0x6c, 0xd0, 0xef, 0x0f};

void strip_trailing_spaces(char *cp)
{
  int i;

  i = 9;
  while ((i >= 0) && (cp[i] == ' '))
  {
    cp[i] = '\0';
    i--;
  }
}

void async_dch_parser_impl::message(pmt::pmt_t msg)
{
  std::vector<uint8_t> bytes = pmt::u8vector_elements(pmt::cdr(msg));
  pmt::pmt_t dict;
  pmt::pmt_t value;
  char buff[11];
  int frame_number;
  int i;

  dict = pmt::car(msg);
  if (!pmt::is_dict(dict))
    return;

  value = pmt::dict_ref(dict, pmt::intern("frame_number"), pmt::PMT_NIL);
  if (!pmt::is_integer(value))
    return; 

  frame_number = pmt::to_long(value);

  for (i=0; i<10; i++)
  {
    buff[i] = scramble[i] ^ bytes[i];
  }
  buff[10] = '\0';

  switch (frame_number)
  {
    case 1:
      strip_trailing_spaces(buff);
      message_port_pub(d_port_callsign, pmt::cons(pmt::intern("callsign"),
        pmt::intern(buff)));
      break;
    case 6:
    case 7:
      {
      std::vector<uint8_t> vec(buff, buff + 10);
      message_port_pub(d_port_location, pmt::cons(pmt::make_dict(),
        pmt::init_u8vector(10, vec)));
      }
      /* printf("%s\n", buff); */
      break;
    default:
      break;
  }
}

/*
 * The private constructor
 */
async_dch_parser_impl::async_dch_parser_impl()
    : gr::sync_block(
          "async_dch_parser",
          gr::io_signature::make(0, 0, 0),
          gr::io_signature::make(0, 0, 0))
{
  d_port_in = pmt::mp("in");
  message_port_register_in(d_port_in);
  set_msg_handler(d_port_in,
    [this](pmt::pmt_t msg) { this->message(msg); });
  d_port_callsign = pmt::mp("callsign");
  message_port_register_out(d_port_callsign);
  d_port_location = pmt::mp("location");
  message_port_register_out(d_port_location);
}

/*
 * Our virtual destructor.
 */
async_dch_parser_impl::~async_dch_parser_impl() {}

int async_dch_parser_impl::work(int noutput_items,
                                gr_vector_const_void_star &input_items,
                                gr_vector_void_star &output_items) {

  // Do <+signal processing+>

  // Tell runtime system how many output items we produced.
  return noutput_items;
}

} /* namespace ysf2 */
} /* namespace gr */
