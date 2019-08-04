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

#ifndef INCLUDED_YSF2_FICH_SOURCE_B_IMPL_H
#define INCLUDED_YSF2_FICH_SOURCE_B_IMPL_H

#include <ysf2/fich_source_b.h>

namespace gr {
  namespace ysf2 {

    class fich_source_b_impl : public fich_source_b
    {
     private:
      int d_frame_number;
      unsigned char d_squelch;

     public:
      fich_source_b_impl();
      ~fich_source_b_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace ysf2
} // namespace gr

#endif /* INCLUDED_YSF2_FICH_SOURCE_B_IMPL_H */

