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


#ifndef INCLUDED_YSF2_DCH_ERRORS_BB_H
#define INCLUDED_YSF2_DCH_ERRORS_BB_H

#include <ysf2/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace ysf2 {

    /*!
     * \brief <+description of block+>
     * \ingroup ysf2
     *
     */
    class YSF2_API dch_errors_bb : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<dch_errors_bb> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ysf2::dch_errors_bb.
       *
       * To avoid accidental use of raw pointers, ysf2::dch_errors_bb's
       * constructor is in a private implementation
       * class. ysf2::dch_errors_bb::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace ysf2
} // namespace gr

#endif /* INCLUDED_YSF2_DCH_ERRORS_BB_H */

