/*!
 * @file       device.hpp
 * @brief      Declares classes for defining %Icom devices
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

#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <string>
#include <array>
#include <algorithm>

#define STRING_TO_ENUM(NAME) inline NAME ## _t NAME ## FromName(const std::string& name) { const NAME ## Names_t::const_iterator it = std::find(NAME ## Names.cbegin(), NAME ## Names.cend(), name); if(it == NAME ## Names.cend()) throw; return (NAME ## _t)(it - NAME ## Names.cbegin()); }

//! Contains all elements for controlling %Icom devices
namespace Icom
{
    //! Enumeration for indicating command status
    enum model_t: uint8_t
    {
        ICR9500
    };

    typedef std::array<std::string, 1> modelNames_t;
    extern const modelNames_t modelNames;
    STRING_TO_ENUM(model)

    //! Structure for representing an %Icom device
    /*!
     * @date    September 8, 2015
     * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
     */
    struct device_t
    {
        model_t model;    //!< model_t of device
        uint8_t address;  //!< CI-V address of device
    };
}

#endif
