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

#include <math.h>

#include <gnuradio/io_signature.h>
#include "vech_decode_fb_impl.h"

namespace gr {
  namespace ysf2 {

    vech_decode_fb::sptr
    vech_decode_fb::make()
    {
      return gnuradio::get_initial_sptr
        (new vech_decode_fb_impl());
    }

    /*
     * The private constructor
     */
    vech_decode_fb_impl::vech_decode_fb_impl()
      : gr::block("vech_decode_fb",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)))
    {
      set_output_multiple(49);
      set_tag_propagation_policy(TPP_DONT);
      d_offset = 0;
    }

    /*
     * Our virtual destructor.
     */
    vech_decode_fb_impl::~vech_decode_fb_impl()
    {
    }

    void
    vech_decode_fb_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = (noutput_items/49)*104;
    }

    int
    vech_decode_fb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];
      int i;
      int j;
      int k;
      int blocks;
      float sum;
      float error;
      float bit;
      std::vector<tag_t> tags;
      unsigned long long block_num;
      unsigned int block_offset;


      blocks = noutput_items/49;
      for (i=0; i<blocks; i++)
      {
	error = 0.0;
        for (j=0.0; j<27;j++)
        {
          sum = 0;
          for (k=0; k<3; k++)
          {
            sum += in[104*i + 3*j + k];
          }
	  if (sum > 0.0)
          {
            out[49*i + j] = 1;
	    bit = 0.7071;
	  }
	  else
          {
            out[49*i + j] = 0;
	    bit = -0.7071;
	  }
	  for (k=0; k<3; k++)
          {
	    error += (in[104*i + 3*j + k] - bit)*(in[104*i + 3*j + k] - bit);
	  }
	}
	error = sqrtf(error/27.0);

	for (j=0; j<22; j++)
          out[49*i + 27 + j] = in[104*i + 81 + j] > 0.0 ? 1 : 0;
	 add_item_tag(0, d_offset + 49*i, pmt::string_to_symbol("rms_error"),
            pmt::from_float(error));

      }

      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0)+blocks*104);
      for (i=0; i<tags.size(); i++)
      {
        block_num = tags[i].offset/104;
        block_offset = tags[i].offset - 104*block_num;
        if (block_offset >= 83)
          block_offset = block_offset - 83 + 27;
        else
          block_offset = block_offset/3;
        add_item_tag(0, block_num*49 + block_offset, tags[i].key, tags[i].value);
      }

      d_offset += blocks*49;

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (blocks*104);

      // Tell runtime system how many output items we produced.
      return blocks*49;
    }

  } /* namespace ysf2 */
} /* namespace gr */

