/* CirKit: A circuit toolkit
 * Copyright (C) 2009-2015  University of Bremen
 * Copyright (C) 2015-2016  EPFL
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

#include "paged_memory.hpp"

#include <boost/assign/std/vector.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>
#include <boost/range/numeric.hpp>

using namespace boost::assign;

namespace cirkit
{

/******************************************************************************
 * paged_memory::set                                                          *
 ******************************************************************************/

paged_memory::set::set( unsigned address, const std::vector<unsigned>& data )
  : address( address ),
    data( data )
{
}

std::size_t paged_memory::set::size() const
{
  return data[address];
}

paged_memory::set::iterator paged_memory::set::begin() const
{
  return data.begin() + address + 1;
}

paged_memory::set::iterator paged_memory::set::end() const
{
  return data.begin() + address + 1 + size();
}

boost::iterator_range<paged_memory::set::iterator> paged_memory::set::range() const
{
  return boost::make_iterator_range( begin(), end() );
}

/******************************************************************************
 * paged_memory::iterator                                                     *
 ******************************************************************************/

paged_memory::iterator::iterator( unsigned index, unsigned address, const std::vector<unsigned>& data )
  : index( index ),
    address( address ),
    data( data )
{
}

paged_memory::iterator::reference paged_memory::iterator::operator*() const
{
  return set( address, data );
}

paged_memory::iterator& paged_memory::iterator::operator++()
{
  address += data[address] + 1u;
  ++index;
  return *this;
}

paged_memory::iterator paged_memory::iterator::operator++(int)
{
  iterator tmp( *this );
  ++*this;
  return tmp;
}

bool paged_memory::iterator::operator==( iterator const& it ) const
{
  return index == it.index;
}

bool paged_memory::iterator::operator!=( iterator const& it ) const
{
  return !( *this == it );
}

/******************************************************************************
 * paged_memory                                                               *
 ******************************************************************************/

paged_memory::paged_memory( unsigned n )
  : _offset( n ),
    _count( n, 0u )
{
  _data.reserve( n << 1u );
}

unsigned paged_memory::count( unsigned index ) const
{
  return _count[index];
}

unsigned paged_memory::memory() const
{
  return sizeof( unsigned ) * ( _data.size() + _offset.size() + _count.size() + 2u ) + sizeof( double );
}

boost::iterator_range<paged_memory::iterator> paged_memory::sets( unsigned index ) const
{
  return boost::make_iterator_range( iterator( 0u, _offset[index], _data ),
                                     iterator( _count[index], 0, _data ) );
}

unsigned paged_memory::sets_count() const
{
  return boost::accumulate( _count, 0u );
}

void paged_memory::assign_empty( unsigned index )
{
  _offset[index] = _data.size();
  _count[index] = 1u;
  _data += 0u;
}

void paged_memory::assign_singleton( unsigned index, unsigned value )
{
  _offset[index] = _data.size();
  _count[index] = 1u;
  _data += 1u,value;
}

void paged_memory::append_begin( unsigned index )
{
  _offset[index] = _data.size();
}

void paged_memory::append_singleton( unsigned index, unsigned value )
{
  _count[index]++;
  _data += 1u,value;
}

void paged_memory::append_set( unsigned index, const std::vector<unsigned>& values )
{
  _count[index]++;
  _data += values.size();
  boost::push_back( _data, values );
}

}

// Local Variables:
// c-basic-offset: 2
// eval: (c-set-offset 'substatement-open 0)
// eval: (c-set-offset 'innamespace 0)
// End:
