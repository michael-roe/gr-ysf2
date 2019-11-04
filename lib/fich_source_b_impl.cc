/* -*- c++ -*- */
/* 
 * Copyright 2019 Michael Roe.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "fich_source_b_impl.h"

namespace gr {
  namespace ysf2 {

    fich_source_b::sptr
    fich_source_b::make()
    {
      return gnuradio::get_initial_sptr
        (new fich_source_b_impl());
    }

    /*
     * The private constructor
     */
    fich_source_b_impl::fich_source_b_impl()
      : gr::sync_block("fich_source_b",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, sizeof(unsigned char)))
    {
      set_output_multiple(32);
      d_frame_number = 0;
      d_squelch = 0;
      d_narrowband = 1;
      d_data_type = 2;
    }

    /*
     * Our virtual destructor.
     */
    fich_source_b_impl::~fich_source_b_impl()
    {
    }

    int
    fich_source_b_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];
      int blocks;
      int i;

      blocks = noutput_items/32;

      for (i=0; i<blocks; i++)
      {
        /* Frame Information */
        out[32*i] = 0;
	out[32*i + 1] = 1;
	/* Callsign Information */
	out[32*i + 2] = 1;
	out[32*i + 3] = 0;
	/* Call Mode */
	out[32*i + 4] = 0;
        out[32*i + 5] = 1;
        /* Block Number */
	out[32*i + 6] = 0;
	out[32*i + 7] = 0;
	/* Block Total */
	out[32*i + 8] = 0;
	out[32*i + 9] = 0;
	/* Frame Number */
	out[32*i + 10] = (d_frame_number >> 2) & 0x1;
	out[32*i + 11] = (d_frame_number >> 1) & 0x1;
	out[32*i + 12] = d_frame_number & 0x1;
        /* Frame Total */
	out[32*i + 13] = 1;
	out[32*i + 14] = 1;
	out[32*i + 15] = 1;
	/* Reserved */
	out[32*i + 16] = 0;
	/* Frequency Deviation */
	out[32*i + 17] = d_narrowband & 0x1;;
	/* Message Path */
	out[32*i + 18] = 0;
	out[32*i + 19] = 0;
	out[32*i + 20] = 0;
	/* VoIP Path */
	out[32*i + 21] = 0;
	/* Data Type */
	out[32*i + 22] = (d_data_type >> 1) & 0x1;
	out[32*i + 23] = d_data_type & 0x1;;
	/* Squelch Enabled */
	if (d_squelch == 0)
        {
	  out[32*i + 24] = 0;
	}
	else
	{
	  out[32*i + 24] = 1;
	}
	/* Squelch */
	out[32*i + 25] = (d_squelch >> 6) & 0x1;
	out[32*i + 26] = (d_squelch >> 5) & 0x1;
	out[32*i + 27] = (d_squelch >> 4) & 0x1;
	out[32*i + 28] = (d_squelch >> 3) & 0x1;
	out[32*i + 29] = (d_squelch >> 2) & 0x1;
	out[32*i + 30] = (d_squelch >> 1) & 0x1;
	out[32*i + 31] = d_squelch & 0x1;

	d_frame_number = (d_frame_number + 1) & 0x7;
      }

      // Tell runtime system how many output items we produced.
      return blocks*32;
    }

  } /* namespace ysf2 */
} /* namespace gr */

