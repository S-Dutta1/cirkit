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

/**
 * @file gen_reciprocal.hpp
 *
 * @brief Generate reciprocal circuit
 *
 * @author Mathias Soeken
 * @since  2.3
 */

#ifndef CLI_GEN_RECIPROCAL_COMMAND_HPP
#define CLI_GEN_RECIPROCAL_COMMAND_HPP

#include <core/cli/cirkit_command.hpp>

namespace cirkit
{

class gen_reciprocal_command : public cirkit_command
{
public:
  gen_reciprocal_command( const environment::ptr& env );

protected:
  rules_t validity_rules() const;
  bool execute();

public:
  log_opt_t log() const;

private:
  unsigned algorithm = 0u;
  unsigned method = 0u;
  unsigned bitwidth = 8u;
  unsigned iterations;
  std::string verilog_name = "/tmp/test.v";
  std::string esop_name    = "/tmp/test.esop";
  std::string pla_name     = "/tmp/test.pla";
  std::string blif_name    = "/tmp/test.blif";
};

}

#endif

// Local Variables:
// c-basic-offset: 2
// eval: (c-set-offset 'substatement-open 0)
// eval: (c-set-offset 'innamespace 0)
// End:
