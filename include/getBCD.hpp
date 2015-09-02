/*!
 * @file       getBCD.hpp
 * @brief      Declares the Icom::getBCD function
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

#ifndef GETBCD_HPP
#define GETBCD_HPP

#include "Command.hpp"

//! Contains all elements for controlling %Icom devices
namespace Icom
{
   //! Sole constructor
   /*!
    * @param   [in] destination The CI-V address of the destination device.
    * @param   [in] source The CI-V address of the source controller.
    * @date    September 2, 2015
    * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
    */
   uint64_t getBCD(
         Buffer::const_iterator start,
         Buffer::const_iterator end);
}

#endif
