/*!
 * @file       Device.hpp
 * @brief      Declares the Icom::Device class
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

#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <string>
#include <array>

//! Contains all elements for controlling %Icom devices
namespace Icom
{
   //! Enumeration for indicating command status
   enum Model {
         ICR9500};

   typedef std::array<std::string, 1> ModelNames;
   extern const ModelNames modelNames;

   //! Structure for representing an %Icom device
   /*!
    * @date    September 4, 2015
    * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
    */
   struct Device
   {
      Model model;            //!< Model of device
      unsigned char address;  //!< CI-V address of device
   };
}

#endif
