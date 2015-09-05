/*!
 * @file       getBCD.cpp
 * @brief      Defines the Icom::getBCD function
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

#include "BCD.hpp"

uint64_t Icom::getBCD(
      const Buffer::const_iterator start,
      const Buffer::const_iterator end)
{
   if(end-start>10)
      return 0;

   uint64_t number=0;
   uint64_t multiplier=1;
   uint64_t digit;

   for(Buffer::const_iterator byte=start; byte != end; ++byte)
   {
      digit = (*byte&0x0f);
      if(digit>9)
         return 0;
      number += digit*(multiplier);
      multiplier *= 10;
      
      digit = (*byte>>4);
      if(digit>9)
         return 0;
      number += digit*(multiplier);
      multiplier *= 10;
   }

   return number;
}

void Icom::putBCD(
      const Buffer::iterator start,
      const Buffer::iterator end,
      uint64_t number)
{
   uint64_t divider=10;
   unsigned char digit;

   for(Buffer::iterator byte=start; byte!=end; ++byte)
   {
      digit = (unsigned char)(number%10);
      *byte = digit&0x0f;
      number /= divider;

      digit = (unsigned char)(number%10);
      *byte |= digit<<4;
      number /= divider;
   }
}
