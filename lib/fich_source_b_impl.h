/* -*- c++ -*- */
/*
 * Copyright 2019-2022 Michael Roe.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_YSF2_FICH_SOURCE_B_IMPL_H
#define INCLUDED_YSF2_FICH_SOURCE_B_IMPL_H

#include <gnuradio/ysf2/fich_source_b.h>

namespace gr {
namespace ysf2 {

class fich_source_b_impl : public fich_source_b {
private:
  int d_frame_number;
  int d_narrowband;
  int d_data_type;
  unsigned char d_squelch;


public:
  fich_source_b_impl(int data_type, int narrowband, int squelch);
  ~fich_source_b_impl();

  // Where all the action really happens
  int work(int noutput_items, gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
};

} // namespace ysf2
} // namespace gr

#endif /* INCLUDED_YSF2_FICH_SOURCE_B_IMPL_H */
