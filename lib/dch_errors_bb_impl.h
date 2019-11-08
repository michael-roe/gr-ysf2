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

#ifndef INCLUDED_YSF2_DCH_ERRORS_BB_IMPL_H
#define INCLUDED_YSF2_DCH_ERRORS_BB_IMPL_H

#include <ysf2/dch_errors_bb.h>

namespace gr {
  namespace ysf2 {

    class dch_errors_bb_impl : public dch_errors_bb
    {
     private:
      int d_todo;
      int d_position;
      char d_msg[80];

     public:
      dch_errors_bb_impl(const std::string &callsign);
      ~dch_errors_bb_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace ysf2
} // namespace gr

#endif /* INCLUDED_YSF2_DCH_ERRORS_BB_IMPL_H */

