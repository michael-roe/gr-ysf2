/* -*- c++ -*- */
/*
 * Copyright 2019-2022 Michael Roe.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "fich_source_b_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace ysf2 {

fich_source_b::sptr fich_source_b::make(int data_type, int narrowband,
                                        int squelch) {
  return gnuradio::make_block_sptr<fich_source_b_impl>(data_type, narrowband,
                                                       squelch);
}

/*
 * The private constructor
 */
fich_source_b_impl::fich_source_b_impl(int data_type, int narrowband,
                                       int squelch)
    : gr::sync_block(
          "fich_source_b",
          gr::io_signature::make(0, 0, 0),
          gr::io_signature::make(1, 1, sizeof(char)))
{
  set_output_multiple(48);
  d_frame_number = 0;
  d_squelch = squelch;
  d_narrowband = narrowband;
  d_data_type = data_type;
}

/*
 * Our virtual destructor.
 */
fich_source_b_impl::~fich_source_b_impl() {}

int fich_source_b_impl::work(int noutput_items,
                             gr_vector_const_void_star &input_items,
                             gr_vector_void_star &output_items) {

  int i;
  int j;
  int blocks;
  unsigned char *out = (unsigned char *) output_items[0];

  blocks = noutput_items/48;

  for (i=0; i<blocks; i++)
  {
    /* Frame Information */
    out[48*i] = 0;
    out[48*i + 1] = 1;
    /* Callsign Information */
    out[48*i + 2] = 1;
    out[48*i + 3] = 0;
    /* Call Mode */
    out[48*i + 4] = 0;
    out[48*i + 5] = 1;
    /* Block Number */
    out[48*i + 6] = 0;
    out[48*i + 7] = 0;
    /* Block Total */
    out[48*i + 8] = 0;
    out[48*i + 9] = 0;
    /* Frame Number */
    out[48*i + 10] = (d_frame_number >> 2) & 0x1;
    out[48*i + 11] = (d_frame_number >> 1) & 0x1;
    out[48*i + 12] = d_frame_number & 0x1;
    /* Frame Total */
    out[48*i + 13] = 1;
    out[48*i + 14] = 1;
    out[48*i + 15] = 1;
    /* Reserved */
    out[48*i + 16] = 0;
    /* Frequency Deviation */
    out[48*i + 17] = d_narrowband & 0x1;;
    /* Message Path */
    out[48*i + 18] = 0;
    out[48*i + 19] = 0;
    out[48*i + 20] = 0;
    /* VoIP Path */
    out[48*i + 21] = 0;
    /* Data Type */
    out[48*i + 22] = (d_data_type >> 1) & 0x1;
    out[48*i + 23] = d_data_type & 0x1;
    /* Squelch Enabled */
    if (d_squelch == 0)
    {
      out[48*i + 24] = 0;
    }
    else
    {
      out[48*i + 24] = 1;
    }
    /* Squelch */
    out[48*i + 25] = (d_squelch >> 6) & 0x1;
    out[48*i + 26] = (d_squelch >> 5) & 0x1;
    out[48*i + 27] = (d_squelch >> 4) & 0x1;
    out[48*i + 28] = (d_squelch >> 3) & 0x1;
    out[48*i + 29] = (d_squelch >> 2) & 0x1;
    out[48*i + 30] = (d_squelch >> 1) & 0x1;
    out[48*i + 31] = d_squelch & 0x1;

    for (j=32; j<48; j++)
    {
      out[48*i + j] = 0;
    }

    d_frame_number = (d_frame_number + 1) & 0x7;
    printf("frame_number = %d\n", d_frame_number);
  }

  // Tell runtime system how many output items we produced.
  return noutput_items;
}

} /* namespace ysf2 */
} /* namespace gr */
