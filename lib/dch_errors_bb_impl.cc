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
#include "dch_errors_bb_impl.h"

namespace gr {
  namespace ysf2 {

    dch_errors_bb::sptr
    dch_errors_bb::make()
    {
      return gnuradio::get_initial_sptr
        (new dch_errors_bb_impl());
    }

    /*
     * The private constructor
     */
    dch_errors_bb_impl::dch_errors_bb_impl()
      : gr::sync_block("dch_errors_bb",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)))
    {
      const char *callsign = "M0GXM";
      const char hwid[] = {0x46, 0x30, 0x64, 0x4f, 0x31};
      int i;

      d_todo = 0;
      memset(d_msg, 32, 80);

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

      /* Location */
      memset(d_msg + 60, 0, 20);
    }

    /*
     * Our virtual destructor.
     */
    dch_errors_bb_impl::~dch_errors_bb_impl()
    {
    }

    int
    dch_errors_bb_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      char *out = (char *) output_items[0];
      int i;
      int tag_index;
      int frame_number;
      std::vector<tag_t> tags;

      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0) + noutput_items);
      tag_index = 0;
      while ((tag_index < tags.size()) && (!pmt::equal(tags[tag_index].key, pmt::intern("frame_number"))))
      {
        tag_index++;
      }

      for (i=0; i<noutput_items; i++)
      {
        if (d_todo == 0)
	{
          if (tag_index >= tags.size())
	  {
            fprintf(stderr, "frame_number tag not found.\n");
	    frame_number = 0;
	  }
	  else
          {
	    frame_number = pmt::to_long(tags[tag_index].value);
	    tag_index++;
            while ((tag_index < tags.size()) &&
	      (!pmt::equal(tags[tag_index].key, pmt::intern("frame_number"))))
            {
              tag_index++;
            }
	  }
	  d_todo = 10;
	  d_position = frame_number*10;
	}
        out[i] = in[i] ^ d_msg[d_position];
	d_todo--;
	d_position++;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace ysf2 */
} /* namespace gr */

