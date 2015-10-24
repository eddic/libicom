/*!
 * @file       bcd.hpp
 * @brief      Declares functions for handling binary coded decimal
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

#ifndef BCD_HPP
#define BCD_HPP

#include "libicom/command.hpp"

//! Contains all elements for controlling %Icom devices
namespace Icom
{
    //! Extract a binary coded decimal number from a string of bytes
    /*!
     * @param   [in] start Iterator to the start of the data
     * @param   [in] end Iterator to the end of the data
     * @date    September 4, 2015
     * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
     */
    uint64_t getBCD(
            const Buffer::const_iterator start,
            const Buffer::const_iterator end);

    //! Insert a binary coded decimal number into a string of bytes
    /*!
     * @param   [out] start Iterator to data start
     * @param   [out] start Iterator to data end
     * @param   [in] number Number to convert to %BCD
     * @date    September 4, 2015
     * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
     */
    void putBCD(
            const Buffer::iterator start,
            const Buffer::iterator end,
            uint64_t number);
}

#endif
