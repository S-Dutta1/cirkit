/* CirKit: A circuit toolkit
 * Copyright (C) 2009-2015  University of Bremen
 * Copyright (C) 2015-2016  EPFL
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file aig_support.hpp
 *
 * @brief Calculates the support of an AIG
 *
 * @author Mathias Soeken
 * @since  2.0
 */

#ifndef AIG_SUPPORT_HPP
#define AIG_SUPPORT_HPP

#include <map>

#include <boost/dynamic_bitset.hpp>

#include <core/properties.hpp>
#include <classical/aig.hpp>

namespace cirkit
{

using support_map_t = std::map<aig_function, boost::dynamic_bitset<>>;

support_map_t aig_structural_support( const aig_graph& aig,
                                      properties::ptr settings = properties::ptr(),
                                      properties::ptr statistics = properties::ptr() );

boost::dynamic_bitset<> get_functional_support( const boost::dynamic_bitset<>& u, unsigned po, unsigned num_pis );
boost::dynamic_bitset<> get_functional_support( const boost::dynamic_bitset<>& u, unsigned po, const aig_graph_info& info );
boost::dynamic_bitset<> get_functional_support( const boost::dynamic_bitset<>& u, unsigned po, const aig_graph& aig );

support_map_t aig_functional_support( const aig_graph& aig );

}

#endif

// Local Variables:
// c-basic-offset: 2
// eval: (c-set-offset 'substatement-open 0)
// eval: (c-set-offset 'innamespace 0)
// End:
