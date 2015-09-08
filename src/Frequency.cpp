/*!
 * @file       Frequency.cpp
 * @brief      Defines the Icom::GetFrequency class
 * @author     Eddie Carle &lt;eddie@isatec.ca&gt;
 * @date       September 8, 2015
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

#include <limits>

#include "Frequency.hpp"
#include "bcd.hpp"

bool Icom::GetFrequency::subcomplete()
{
   m_frequency=0;

   if(m_result.size() && m_result.front() == code)
   {
      const uint64_t bigBCD = getBCD(m_result.begin()+1, m_result.end());

      if(bigBCD <= (uint64_t)(std::numeric_limits<unsigned int>::max()))
         m_frequency = (unsigned int)bigBCD;
   }

   if(m_frequency)
      m_status=SUCCESS;
   else
      m_status=PARSEERROR;

   return true;
}

Icom::Frequency::Frequency(
      const Device& dev,
      unsigned int freq,
      bool reply):
   Command_base(dev, reply),
   m_frequency(freq)
{
}

Icom::GetFrequency::GetFrequency(const Device& dev):
   Frequency(dev, 0)
{
   m_command.push_back(code);
}

Icom::SetFrequency::SetFrequency(const Device& dev, unsigned int frequency):
   Frequency(dev, frequency, false)
{
   m_command.resize(6);
   m_command.front() = code;
   putBCD(m_command.begin()+1, m_command.end(), m_frequency);
}
