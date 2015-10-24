/*!
 * @file       Duplex.cpp
 * @brief      Defines the classes for setting/getting the operating
 *             duplex of an %Icom device.
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
#include <cmath>

#include "libicom/duplex.hpp"
#include "bcd.hpp"

bool Icom::GetDuplex::subcomplete()
{
    if(m_result.size() == 4 && m_result.front() == code)
    {
        m_offset = (unsigned int)getBCD(m_result.begin()+1, m_result.end());
        m_status=SUCCESS;
    }
    else
        m_status=PARSEERROR;

    return true;
}

Icom::GetDuplex::GetDuplex(const device_t& dev):
    Command_base(dev)
{
    m_command.push_back(code);
}

Icom::SetDuplex::SetDuplex(
        const device_t& dev,
        int offset):
    Command_base(dev),
    m_started(false),
    m_offset(offset)
{
    m_command.push_back(mode_code);
    if(offset==0)
        m_command.push_back(0x10);
    else if(offset < 0)
        m_command.push_back(0x11);
    else
        m_command.push_back(0x12);
}

const uint8_t Icom::GetDuplex::code;
const uint8_t Icom::SetDuplex::mode_code;
const uint8_t Icom::SetDuplex::offset_code;

bool Icom::SetDuplex::subcomplete()
{
    if(!m_started)
    {
        if(m_offset)
        {
            m_command.resize(4);
            m_command.front()=offset_code;
            putBCD(m_command.begin()+1, m_command.end(), std::abs(m_offset));
            m_started = true;
            return false;
        }
        else
        {
            m_started=SUCCESS;
            return true;
        }
    }
    
    m_started=SUCCESS;
    return true;
}
