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
#include "dch_parser_b_impl.h"

namespace gr {
  namespace ysf2 {

    dch_parser_b::sptr
    dch_parser_b::make()
    {
      return gnuradio::get_initial_sptr
        (new dch_parser_b_impl());
    }

    /*
     * The private constructor
     */
    dch_parser_b_impl::dch_parser_b_impl()
      : gr::sync_block("dch_parser_b",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(0, 0, 0))
    {
      set_output_multiple(10);
      d_port = pmt::mp("callsign_data");
      message_port_register_out(d_port);
    }

    /*
     * Our virtual destructor.
     */
    dch_parser_b_impl::~dch_parser_b_impl()
    {
    }

    int
    dch_parser_b_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      int i;
      int j;
      int crc_error;
      int frame_number;
      std::vector<tag_t> tags;
      char callsign[9];
      int len;

      // Do <+signal processing+>
      for (i=0; i<noutput_items/8; i++)
      {
	get_tags_in_range(tags, 0, nitems_read(0) + 8*i,
	  nitems_read(0) + 8*i + 8);

	crc_error = 0;
	frame_number = -1;
        for (j=0; j<tags.size(); j++)
        {
          if (pmt::equal(tags[j].key, pmt::intern("crc_error")))
	  {
	    if (pmt::equal(tags[j].value, pmt::PMT_T))
              crc_error = 1;
	  }
	  if (pmt::equal(tags[j].key, pmt::intern("frame_number")))
          {
            frame_number = pmt::to_long(tags[j].value);
	  }
	}
	if ((crc_error == 0) && (frame_number == 1))
        {
	  fprintf(stderr, "dch_parser: ");
	  for (j=0; j<8; j++)
	  {
	    fprintf(stderr, "%c", in[8*i + j]);
	  }
	  fprintf(stderr, "\n");
	  memcpy(callsign, in + 8*i, 8);
	  len = 8;
	  while ((len > 0) && (callsign[len - 1] == ' '))
	  {
            len--;
	  }
	  callsign[len] = '\0';
	  message_port_pub(d_port, pmt::intern(callsign));
	}
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace ysf2 */
} /* namespace gr */

