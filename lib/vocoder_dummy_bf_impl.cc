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
      d_deleted_frame_key = pmt::intern("deleted_frame");
    }

    /*
     * Our virtual destructor.
     */
    vocoder_dummy_bf_impl::~vocoder_dummy_bf_impl()
    {
    }

    static float random_gaussian()
    {
      float r;

      r = ((float) random())/((float) RAND_MAX) - 0.5;
      r += ((float) random())/((float) RAND_MAX) - 0.5;
      r += ((float) random())/((float) RAND_MAX) - 0.5;
      return r;
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
      std::vector<tag_t> tags;
      int i;
      int j;
      int phase;
      int offset;

      for (i=0; i<noutput_items; i++)
      {
	phase = i % 80;
        out[i] = sin(((float) phase)*M_PI*2.0/80.0);
      }
      
      get_tags_in_range(tags, 0, nitems_read(0), 
        nitems_read(0)+(noutput_items/4800)*49*5);

      for (i=0; i<tags.size(); i++)
      {
        if (pmt::equal(tags[i].key, d_deleted_frame_key))
        {
          offset = (tags[i].offset - nitems_read(0))/49;
	  if ((offset < 0) || (960*offset > noutput_items))
	    fprintf(stderr, "offset = %d, noutput_items = %d\n", offset, noutput_items);
	  for (j=0; j<960;j++)
	  {
	    out[offset*960 + j] = random_gaussian();
	  }
	}
      }
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each ((noutput_items/4800)*49*5);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace ysf2 */
} /* namespace gr */

