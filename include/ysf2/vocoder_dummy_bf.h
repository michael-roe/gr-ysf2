/* -*- c++ -*- */
/* 
 * Copyright 2019 <+YOU OR YOUR COMPANY+>.
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


#ifndef INCLUDED_YSF2_VOCODER_DUMMY_BF_H
#define INCLUDED_YSF2_VOCODER_DUMMY_BF_H

#include <ysf2/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace ysf2 {

    /*!
     * \brief <+description of block+>
     * \ingroup ysf2
     *
     */
    class YSF2_API vocoder_dummy_bf : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<vocoder_dummy_bf> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ysf2::vocoder_dummy_bf.
       *
       * To avoid accidental use of raw pointers, ysf2::vocoder_dummy_bf's
       * constructor is in a private implementation
       * class. ysf2::vocoder_dummy_bf::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace ysf2
} // namespace gr

#endif /* INCLUDED_YSF2_VOCODER_DUMMY_BF_H */

