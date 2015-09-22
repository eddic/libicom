/*!
 * @file       Mode.cpp
 * @brief      Defines the classes for setting/getting the operating
 *             mode of an %Icom device.
 * @author     Eddie Carle &lt;eddie@isatec.ca&gt;
 * @date       September 21, 2015
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

#include "libicom/mode.hpp"

bool Icom::GetMode::subcomplete()
{
   m_mode=(mode_t)0xff;
   m_filter=(filter_t)0xff;

   if(m_result.front() == code)
   {
      if(m_result.size()>1)
      {
         m_mode=(mode_t)m_result[1];

         switch(m_result.size())
         {
            case 2:
               m_filter=filter_t::NONE;
               break;
            case 3:
               m_filter=(filter_t)m_result[2];
               break;
         }
      }
   }

   if(m_mode < modeNames.size() && m_filter < filterNames.size())
      m_status=SUCCESS;
   else
      m_status=PARSEERROR;

   return true;
}

Icom::GetMode::GetMode(const device_t& dev):
   Command_base(dev)
{
   m_command.push_back(code);
}

Icom::SetMode::SetMode(
      const device_t& dev,
      mode_t mode,
      filter_t filter):
   Command_base(dev)
{
   m_command.push_back(code);
   m_command.push_back((uint8_t)mode);
   if(filter != filter_t::NONE)
      m_command.push_back((uint8_t)filter);
}

const Icom::modeNames_t Icom::modeNames = {
      "LSB",
      "USB",
      "AM",
      "CW",
      "FSK",
      "FM",
      "WFM",
      "CW-R",
      "FSK-R",
      "","","","","","","","",
      "S-AM(D)",
      "","",
      "S-AM(L)",
      "S-AM(U)",
      "P25"};

const Icom::filterNames_t Icom::filterNames = {
      "N/A",
      "1/wide",
      "2/medium",
      "3/narrow"};

const uint8_t Icom::SetMode::code;
const uint8_t Icom::GetMode::code;
