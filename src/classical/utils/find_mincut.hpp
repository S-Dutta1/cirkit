/* RevKit: A Toolkit for Reversible Circuit Design (www.revkit.org)
 * Copyright (C) 2009-2013  The RevKit Developers <revkit@informatik.uni-bremen.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file find_mincut.hpp
 *
 * @brief Find Min-Cut in AIG graph
 *
 * @author Mathias Soeken
 * @since  2.0
 */

#ifndef FIND_MINCUT_HPP
#define FIND_MINCUT_HPP

#include <list>

#include <classical/utils/aig_to_graph.hpp>

namespace revkit
{

  void find_mincut( aig_graph& graph, std::list<unsigned>& cut );

}

#endif

// Local Variables:
// c-basic-offset: 2
// End:
