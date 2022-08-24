/* -*- c++ -*- */
/*
 * Copyright 2022 Michael Roe.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_YSF2_ASYNC_DCH_PARSER_H
#define INCLUDED_YSF2_ASYNC_DCH_PARSER_H

#include <gnuradio/sync_block.h>
#include <gnuradio/ysf2/api.h>

namespace gr {
namespace ysf2 {

/*!
 * \brief <+description of block+>
 * \ingroup ysf2
 *
 */
class YSF2_API async_dch_parser : virtual public gr::sync_block {
public:
  typedef std::shared_ptr<async_dch_parser> sptr;

  /*!
   * \brief Return a shared_ptr to a new instance of ysf2::async_dch_parser.
   *
   * To avoid accidental use of raw pointers, ysf2::async_dch_parser's
   * constructor is in a private implementation
   * class. ysf2::async_dch_parser::make is the public interface for
   * creating new instances.
   */
  static sptr make();
};

} // namespace ysf2
} // namespace gr

#endif /* INCLUDED_YSF2_ASYNC_DCH_PARSER_H */
