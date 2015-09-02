/*!
 * @file       Command.cpp
 * @brief      Defines the Icom::Command class
 * @author     Eddie Carle &lt;eddie@isatec.ca&gt;
 * @date       September 2, 2015
 * @copyright  Copyright &copy; 2015 %Isatec Inc.  This project is released
 *             under the GNU General Public License Version 3.
 */

/* Copyright (C) 2015 %Isatec Inc.
 *
 * This file is part of the %Icom CI-V Control Library
 *
 * The %Icom CI-V Control Library is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * The %Icom CI-V Control Library is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * The %Icom CI-V Control Library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Command.hpp"

void Icom::Command_base::complete()
{
   if(
         m_result[0] == 0xfe &&
         m_result[1] == 0xfe &&
         m_result[2] == m_source &&
         m_result[3] == m_destination &&
         m_result.back() == 0xfd)
      subComplete();

   if(m_status != SUCCESS)
      m_status = FAIL;
}

Icom::Command_base(
      const size_t commandSize,
      const size_t resultSize,
      const unsigned char destination,
      const unsigned char source):
   m_destination(destination),
   m_source(source),
   m_status(INCOMPLETE)
{
   m_command.reserve(bufferReserveSize);
   m_result.reserve(bufferReserveSize);
}
