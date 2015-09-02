/*!
 * @file       GetFrequency.cpp
 * @brief      Defines the Icom::GetFrequency class
 * @author     Eddie Carle &lt;eddie@isatec.ca&gt;
 * @date       September 1, 2015
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

#include "GetFrequency.hpp"

void Icom::GetFrequency::subComplete()
{
   if(*resultStart() == 0x03)
   {
      unsigned int multiplier=1;
      m_frequency=0;
      for(auto number = resultStart()+1; number != resultEnd(); ++number)
      {
         m_frequency += (*number&0x0f)*(multiplier);
         multiplier *= 10;
         m_frequency += (*number>>4)*(multiplier);
         multiplier *= 10;
      }
      m_status = SUCCESS;            
   }
}

Icom::GetFrequency::GetFrequency(
      unsigned char destination,
      unsigned char source):
   Command_base(1, 1+5, destination, source),
   m_frequency(0)
{
   *m_commandStart() = 0x03;
}
