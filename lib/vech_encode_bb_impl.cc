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
#include "vech_encode_bb_impl.h"

namespace gr {
  namespace ysf2 {

    vech_encode_bb::sptr
    vech_encode_bb::make()
    {
      return gnuradio::get_initial_sptr
        (new vech_encode_bb_impl());
    }

    /*
     * The private constructor
     */
    vech_encode_bb_impl::vech_encode_bb_impl()
      : gr::block("vech_encode_bb",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)))
    {
      set_output_multiple(104);
      set_tag_propagation_policy(TPP_DONT);
      d_offset = 0;
    }

    /*
     * Our virtual destructor.
     */
    vech_encode_bb_impl::~vech_encode_bb_impl()
    {
    }

    void
    vech_encode_bb_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = (noutput_items/104)*49;
    }

    int
    vech_encode_bb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char*in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];
      int i;
      int j;
      int k;
      int blocks;

      blocks = noutput_items/104;
      for (i=0; i<blocks; i++)
      {
        for (j=0; j<27; j++)
        {
          for (k=0; k<3; k++)
          {
            out[104*i + 3*j + k] = in[49*i + j];
	  }
	}
	for (j=0; j<22; j++)
        {
	  out[104*i + 81 + j] = in[49*i + 27 + j];
        }	  
	out[104*i + 103] = 0;
      }

      d_offset += blocks*104;

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (blocks*49);

      // Tell runtime system how many output items we produced.
      return blocks*104;
    }

  } /* namespace ysf2 */
} /* namespace gr */

