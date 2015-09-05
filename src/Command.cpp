/*!
 * @file       Command.cpp
 * @brief      Defines the Icom::Command class
 * @author     Eddie Carle &lt;eddie@isatec.ca&gt;
 * @date       September 4, 2015
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

Icom::Command_base::Command_base(const Device& dev, bool reply):
   device(dev),
   m_reply(reply),
   m_status(INCOMPLETE)
{
   m_command.reserve(bufferReserveSize);
   m_result.reserve(bufferReserveSize);
}

bool Icom::Command_base::complete()
{
   if(!m_reply)
      m_status = SUCCESS;
   else if(m_result.size() == 1)
   {
      switch(m_result.front())
      {
         case 0xfb:
            m_status = SUCCESS;
            return true;
         case 0xfa:
            m_status = FAIL;
            return true;
      }
   }
   return subcomplete();
}
