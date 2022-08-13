/* -*- c++ -*- */
/*
 * Copyright 2022 Michael Roe.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_YSF2_FICH_PARSER_B_H
#define INCLUDED_YSF2_FICH_PARSER_B_H

#include <gnuradio/sync_block.h>
#include <gnuradio/ysf2/api.h>

namespace gr {
namespace ysf2 {

/*!
 * \brief <+description of block+>
 * \ingroup ysf2
 *
 */
class YSF2_API fich_parser_b : virtual public gr::sync_block {
public:
  typedef std::shared_ptr<fich_parser_b> sptr;

  /*!
   * \brief Return a shared_ptr to a new instance of ysf2::fich_parser_b.
   *
   * To avoid accidental use of raw pointers, ysf2::fich_parser_b's
   * constructor is in a private implementation
   * class. ysf2::fich_parser_b::make is the public interface for
   * creating new instances.
   */
  static sptr make();
};

} // namespace ysf2
} // namespace gr

#endif /* INCLUDED_YSF2_FICH_PARSER_B_H */
