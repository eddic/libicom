/*!
 * @file       Power.hpp
 * @brief      Declares the class for turning an %Icom device on or off
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

#ifndef POWER_HPP
#define POWER_HPP

#include "libicom/command.hpp"

//! Contains all elements for controlling %Icom devices
namespace Icom
{
   enum powerState_t: uint8_t
   {
      OFF   = 0x00,
      ON    = 0x01
   };
   typedef std::array<std::string, 2> powerStateNames_t;
   extern const powerStateNames_t powerStateNames;
   STRING_TO_ENUM(powerState)

   //! Class for turning an %Icom device on or off
   /*!
    * @date    September 8, 2015
    * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
    */
   class Power: public Command_base
   {
   public:
      //! Make a command object
      /*!
       * @param   [in] dev The %Icom device in question
       * @param   [in] state Do we want it on or off?
       * @date    September 8, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      static Power* make(const device_t& dev, powerState_t state)
      {
         return new Power(dev, state);
      }
   private:
      //! Construct the command object
      /*!
       * @param   [in] dev The %Icom device in question
       * @param   [in] state Do we want it on or off?
       * @date    September 8, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      Power(const device_t& dev, powerState_t state);

      static const uint8_t code=0x18;  //!< Command code
   };
}

#endif
