/*!
 * @file       getBCD.cpp
 * @brief      Defines the Icom::getBCD function
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

#include "getBCD.hpp"

uint64_t Icom::getBCD(
      Buffer::const_iterator start,
      Buffer::const_iterator end)
{
   if(end-start>10)
      return 0;

   uint64_t total=0;
   uint64_t multiplier=1;
   uint64_t digit;

   for(Buffer::const_iterator number=start; number != end; ++number)
   {
      digit = (*number&0x0f);
      if(digit>9)
         return 0;
      total += digit*(multiplier);
      multiplier *= 10;
      
      digit = (*number>>4);
      if(digit>9)
         return 0;
      total += digit*(multiplier);
      multiplier *= 10;
   }

   return total;
}
