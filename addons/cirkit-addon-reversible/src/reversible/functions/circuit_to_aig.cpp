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

#include "circuit_to_aig.hpp"

#include <classical/utils/aig_utils.hpp>

namespace cirkit
{

/******************************************************************************
 * Types                                                                      *
 ******************************************************************************/

/******************************************************************************
 * Private functions                                                          *
 ******************************************************************************/

/******************************************************************************
 * Public functions                                                           *
 ******************************************************************************/

aig_graph circuit_to_aig( const circuit& circ )
{
  std::vector<aig_function> fs( circ.lines() );

  aig_graph aig;
  aig_initialize( aig );

  /* I/O vector */
  for ( auto i = 0u; i < circ.lines(); ++i )
  {
    const auto constant = circ.constants()[i];
    if ( constant != boost::none )
    {
      fs[i] = aig_get_constant( aig, *constant );
    }
    else
    {
      fs[i] = aig_create_pi( aig, circ.inputs()[i] );
    }
  }

  /* compute all gates */
  for ( const auto& g : circ )
  {
    const auto target = g.targets().front();

    if ( g.controls().empty() )
    {
      fs[target].complemented ^= 1;
    }
    else
    {
      std::vector<aig_function> operands;
      for ( const auto& c : g.controls() )
      {
        operands += make_function( fs[c.line()], !c.polarity() );
      }
      fs[target] = aig_create_xor( aig, fs[target], aig_create_nary_and( aig, operands ) );
    }
  }

  /* create outputs */
  for ( auto i = 0u; i < circ.lines(); ++i )
  {
    if ( circ.garbage()[i] ) { continue; }

    aig_create_po( aig, fs[i], circ.outputs()[i] );
  }

  return aig;
}

}

// Local Variables:
// c-basic-offset: 2
// eval: (c-set-offset 'substatement-open 0)
// eval: (c-set-offset 'innamespace 0)
// End:
