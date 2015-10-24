/*!
 * @file       squelch.cpp
 * @brief      Defines the classes for checking and managing the
 *             squelch of an %Icom device.
 * @author     Eddie Carle &lt;eddie@isatec.ca&gt;
 * @date       September 23, 2015
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

#include "libicom/squelch.hpp"

bool Icom::SquelchHold::subcomplete()
{
    if(m_result.size() == 3 &&
            m_result[0] == code &&
            m_result[1] == subCode)
    {
        if(m_squelchState == (squelchState_t)m_result[2])
        {
            m_status=SUCCESS;
            return true;
        }
    }
    else
    {
        m_status=PARSEERROR;
        return true;
    }

    return false;
}

const uint8_t Icom::SquelchHold::code;
const uint8_t Icom::SquelchHold::subCode;

Icom::SquelchHold::SquelchHold(const device_t& dev, squelchState_t state):
    Command_base(dev),
    m_squelchState(state)
{
    m_command.resize(3);
    m_command[0] = code;
    m_command[1] = subCode;
}

const Icom::squelchStateNames_t Icom::squelchStateNames = {
        "closed",
        "open"};
