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
#include "vocoder_dummy_bf_impl.h"

namespace gr {
  namespace ysf2 {

    vocoder_dummy_bf::sptr
    vocoder_dummy_bf::make()
    {
      return gnuradio::get_initial_sptr
        (new vocoder_dummy_bf_impl());
    }

    /*
     * The private constructor
     */
    vocoder_dummy_bf_impl::vocoder_dummy_bf_impl()
      : gr::block("vocoder_dummy_bf",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
      set_output_multiple(4800);
    }

    /*
     * Our virtual destructor.
     */
    vocoder_dummy_bf_impl::~vocoder_dummy_bf_impl()
    {
    }

    void
    vocoder_dummy_bf_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = (noutput_items/4800)*49*5;
    }

    int
    vocoder_dummy_bf_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      float *out = (float *) output_items[0];
      int i;
      int phase;

      for (i=0; i<noutput_items; i++)
      {
	phase = i % 80;
        out[i] = sin(((float) phase)*M_PI*2.0/80.0);
      }
      
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each ((noutput_items/4800)*49*5);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace ysf2 */
} /* namespace gr */

