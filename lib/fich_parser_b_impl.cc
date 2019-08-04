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
#include "fich_parser_b_impl.h"

namespace gr {
  namespace ysf2 {

    fich_parser_b::sptr
    fich_parser_b::make()
    {
      return gnuradio::get_initial_sptr
        (new fich_parser_b_impl());
    }

    /*
     * The private constructor
     */
    fich_parser_b_impl::fich_parser_b_impl()
      : gr::sync_block("fich_parser_b",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(0, 0, 0))
    {
      d_port = pmt::mp("header_data");
      message_port_register_out(d_port);
      set_output_multiple(32);
    }

    /*
     * Our virtual destructor.
     */
    fich_parser_b_impl::~fich_parser_b_impl()
    {
    }

    int
    fich_parser_b_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      std::vector<tag_t> tags;
      pmt::pmt_t dict;
      int i;
      int error_found;
      unsigned int frame_type;
      unsigned int callsign_information;
      unsigned int call_mode;
      unsigned int block_number;
      unsigned int block_total;
      unsigned int frame_number;
      unsigned int frame_total;
      unsigned int data_type;
      unsigned int squelch;

      if (noutput_items < 32)
      {
	fprintf(stderr, "not enough bytes for FICH\n");
        return 0;
      }


      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0)+32);

      error_found = 0;
      for (i=0; i<tags.size(); i++)
      {
	if (pmt::equal(tags[i].key, pmt::intern("crc_error")))
        {
	  if (pmt::equal(tags[i].value, pmt::PMT_T))
	    error_found = 1;
	}
	if (pmt::equal(tags[i].key, pmt::intern("parity_error")))
        {
          if (pmt::equal(tags[i].value, pmt::PMT_T))
            error_found = 1;
        }
      }

      if (error_found)
      {
        message_port_pub(d_port, pmt::PMT_F);
      }
      else
      {
        frame_type = (in[0] << 1) | in[1];
        callsign_information = (in[2] << 1) | in[3];
        call_mode = (in[4] << 1) | in[5];
        block_number = (in[6] << 1) | in[7];
        block_total = (in[8] << 1) | in[9];
        frame_number = (in[10] << 2) | (in[11] << 1) | in[12];
        frame_total = (in[13] << 2) | (in[14] << 1) | in[15];
        data_type = (in[22] << 1) | in[23];
	squelch = (in[25] << 6) | (in[26] << 5) |(in[27] << 4) |(in[28] << 3) |
	  (in[29] << 2) | (in[30] << 1) | in[31];

	dict = pmt::make_dict();
	dict = pmt::dict_add(dict, pmt::intern("payload_len"), pmt::from_long(360));
	dict = pmt::dict_add(dict, pmt::intern("frame_type"),
	  pmt::from_long(frame_type));
	dict = pmt::dict_add(dict, pmt::intern("frame_number"),
	  pmt::from_long(frame_number));
	dict = pmt::dict_add(dict, pmt::intern("data_type"),
	  pmt::from_long(data_type));
	if (squelch != 0)
	{
	  dict = pmt::dict_add(dict, pmt::intern("squelch"),
	    pmt::from_long(squelch));
        }
        for (i=0; i<tags.size(); i++)
        {
          if (pmt::equal(tags[i].key, pmt::intern("rx_time")))
          {
	    dict = pmt::dict_add(dict, pmt::intern("header_time"),
	      tags[i].value);
          }
	  else if (pmt::equal(tags[i].key, pmt::intern("skip")))
	  {
	    dict = pmt::dict_add(dict, tags[i].key,
              tags[i].value);
          }
	  else if (pmt::equal(tags[i].key, pmt::intern("low_correlation")))
          {
	    dict = pmt::dict_add(dict, tags[i].key,
              tags[i].value);
          }
	  else if  (pmt::equal(tags[i].key, pmt::intern("burst")))
	  {
            dict = pmt::dict_add(dict, tags[i].key,
              tags[i].value);
          }
	}
	message_port_pub(d_port, dict);
      }

      return 32;
    }

  } /* namespace ysf2 */
} /* namespace gr */

