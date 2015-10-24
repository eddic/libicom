/*!
 * @file       vfo.cpp
 * @brief      Defines classes for selecting and modifying %VFO mode
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

#include "libicom/vfo.hpp"

Icom::VFO::VFO(const device_t& dev, vfoState_t state):
    Command_base(dev)
{
    m_command.push_back(code);
    m_command.push_back((uint8_t)state);
}

const Icom::vfoStateNames_t Icom::vfoStateNames =
{
    "VFO-A",
    "VFO-B",
    "","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","",
    "swap",
    "","","","","","","","","","","","","","","",
    "single",
    "dual"
};

Icom::VFO::VFO(const device_t& dev):
    Command_base(dev)
{
    m_command.push_back(code);
}

const uint8_t Icom::VFO::code;
