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
#include "dch_source_b_impl.h"

namespace gr {
  namespace ysf2 {

    dch_source_b::sptr
    dch_source_b::make()
    {
      return gnuradio::get_initial_sptr
        (new dch_source_b_impl());
    }

    /*
     * The private constructor
     */
    dch_source_b_impl::dch_source_b_impl()
      : gr::sync_block("dch_source_b",
              gr::io_signature::make(0, 0, sizeof(0)),
              gr::io_signature::make(1, 1, sizeof(char)))
    {
      int i;
      const char *callsign = "M0GXM";
      const char hwid[] = {0x46, 0x30, 0x64, 0x4f, 0x31};

      set_output_multiple(10);
      d_frame_number = 0;
      memset(d_msg, ' ', 80);

      /* Destination group - wildcard + source hardware id */
      memset(d_msg, 42, 5);
      memcpy(d_msg + 5, hwid, 5);

      /* Source callsign */
      strncpy(d_msg + 10, callsign, 10);
      for (i = strlen(callsign); i<10; i++)
      {
        d_msg[10 + i] = ' ';
      }

      /* Transmitter id */
      memcpy(d_msg + 55, hwid, 5);
    }

    /*
     * Our virtual destructor.
     */
    dch_source_b_impl::~dch_source_b_impl()
    {
    }

    int
    dch_source_b_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      char *out = (char *) output_items[0];
      int blocks;
      int i;
      int j;

      blocks = noutput_items/10;
      for (i=0; i<blocks; i++)
      {
        for (j=0; j<10; j++)
        {
          *out = d_msg[d_frame_number*10 + j];
	  out++;
	}
	d_frame_number = (d_frame_number + 1) & 0x7;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace ysf2 */
} /* namespace gr */

