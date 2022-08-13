/* -*- c++ -*- */
/*
 * Copyright 2019-2022 Michael Roe.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "fich_parser_b_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace ysf2 {

fich_parser_b::sptr fich_parser_b::make() {
  return gnuradio::make_block_sptr<fich_parser_b_impl>();
}

/*
 * The private constructor
 */
fich_parser_b_impl::fich_parser_b_impl()
    : gr::sync_block(
          "fich_parser_b",
          gr::io_signature::make(1, 1, sizeof(unsigned char)),
          gr::io_signature::make(0, 0, 0))
{
  d_port = pmt::mp("header_data");
  message_port_register_out(d_port);
  set_output_multiple(48);

}

/*
 * Our virtual destructor.
 */
fich_parser_b_impl::~fich_parser_b_impl() {}

int fich_parser_b_impl::work(int noutput_items,
                             gr_vector_const_void_star &input_items,
                             gr_vector_void_star &output_items) {
  unsigned char *in = (unsigned char *) input_items[0];
  pmt::pmt_t dict;
  unsigned int frame_type;
  unsigned int callsign_information;
  unsigned int call_mode;
  unsigned int block_number;
  unsigned int block_total;
  unsigned int frame_number;
  unsigned int frame_total;
  unsigned int data_type;
  unsigned int squelch;
  unsigned int crc;
  unsigned int crc1;
  unsigned int feedback;
  int i;

  crc = 0;
  for (i=0; i<32; i++)
  {
    feedback = in[i] ^ (crc >> 15);
    crc = (crc << 1) & 0xffff;
    if (feedback)
      crc ^= 1 | (1 << 5) | (1 << 12);
  }
  crc1 = 0;
  for (i=32; i<48; i++)
  {
    crc1 = (crc1 << 1) | in[i];
  }
  if ((crc ^ crc1) != 0xffff)
  {
    printf("CRC: %04x %04x %04x\n", crc, crc1, crc ^ crc1);
  }

  frame_type = (in[0] << 1) | in[1];
  callsign_information = (in[2] << 1) | in[3];
  call_mode = (in[4] << 1) | in[5];
  block_number = (in[6] << 1) | in[7];
  block_total = (in[8] << 1) | in[9];
  frame_number = (in[10] << 2) | (in[11] << 1) | in[12];
  frame_total = (in[13] << 2) | (in[14] << 1) | in[15];
  data_type = (in[22] << 1) | in[23];
  squelch = (in[25] << 6) | (in[26] << 5) |(in[27] << 4) |(in[28] << 3) |
    (in[29] << 2) | (in[30] << 1) | in[31];


  dict = pmt::make_dict();
  dict = pmt::dict_add(dict, pmt::intern("payload_len"),
    pmt::from_long(360));
  dict = pmt::dict_add(dict, pmt::intern("frame_type"),
    pmt::from_long(frame_type));
  dict = pmt::dict_add(dict, pmt::intern("frame_number"),
    pmt::from_long(frame_number));

  message_port_pub(d_port, dict);

  // Tell runtime system how many output items we produced.
  return noutput_items;
}

} /* namespace ysf2 */
} /* namespace gr */
