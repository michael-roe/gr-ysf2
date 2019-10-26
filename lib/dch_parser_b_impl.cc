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
      d_port_callsign = pmt::mp("callsign_data");
      message_port_register_out(d_port_callsign);
      d_port_hwid =  pmt::mp("hwid");
      message_port_register_out(d_port_hwid);
      d_port_location =  pmt::mp("location");
      message_port_register_out(d_port_location);
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
      char callsign[11];
      char hwid[11];
      char location[21];
      int len;

      for (i=0; i<noutput_items/10; i++)
      {
	get_tags_in_range(tags, 0, nitems_read(0) + 10*i,
	  nitems_read(0) + 10*i + 10);

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
	if (crc_error == 0)
	{
          if (frame_number == 1)
          {
	    memcpy(callsign, in + 10*i, 10);
	    len = 10;
	    while ((len > 0) && (callsign[len - 1] == ' '))
	    {
              len--;
	    }
	    callsign[len] = '\0';
	    message_port_pub(d_port_callsign, pmt::cons(pmt::intern("callsign"),
	      pmt::intern(callsign)));
	  }
	  else if (frame_number == 5)
	  {
            for (j=0; j<5; j++)
            {
              sprintf(hwid + 2*j, "%02x", in[10*i + j + 5]);
            }
            message_port_pub(d_port_hwid, pmt::cons(pmt::intern("hwid"),
              pmt::intern(hwid)));
          }
	  else if (frame_number == 6)
	  {
	    for (j=0; j<10; j++)
            {
              sprintf(location + 2*j, "%02x", in[10*i + j]);
            }
            message_port_pub(d_port_location, pmt::cons(pmt::intern("location"),
              pmt::intern(location)));
          }
	}
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace ysf2 */
} /* namespace gr */

