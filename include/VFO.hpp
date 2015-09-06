/*!
 * @file       VFO.hpp
 * @brief      Declares the classes for turning an %Icom device on or off
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

#ifndef VFO_HPP
#define VFO_HPP

#include "Command.hpp"

//! Contains all elements for controlling %Icom devices
namespace Icom
{
   enum vfoState_t: uint8_t
   {
      VFO0     = 0x00,
      VFO1     = 0x01,
      VFO2     = 0x02,
      VFO3     = 0x03,
      VFO4     = 0x04,
      VFO5     = 0x05,
      VFO6     = 0x06,
      VFO7     = 0x07,
      VFO8     = 0x08,
      VFO9     = 0x09,
      SWAP     = 0xb0,
      SINGLE   = 0xc0,
      DUAL     = 0xc1
   };
   typedef std::array<std::string, 0xc2> vfoStateNames_t;
   extern const vfoStateNames_t vfoStateNames;
   STRING_TO_ENUM(vfoState)

   //! Base class selecting or configuring VFO mode
   /*!
    * @date    September 6, 2015
    * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
    */
   class VFO: public Command_base
   {
   public:
      //! Make a command object to set the %VFO state
      /*!
       * @param   [in] dev The %Icom Device in question
       * @param   [in] state What state do we want to put the %VFO in?
       * @date    September 6, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      static VFO* make(const Device& dev, vfoState_t state)
      {
         return new VFO(dev, state);
      }

      //! Make a command object to select %VFO mode
      /*!
       * @param   [in] dev The %Icom Device in question
       * @date    September 6, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      static VFO* make(const Device& dev)
      {
         return new VFO(dev);
      }
   private:
      //! Construct the command object to set the %VFO state
      /*!
       * @param   [in] dev The %Icom Device in question
       * @param   [in] state What state do we want to put the %VFO in?
       * @date    September 6, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      VFO(const Device& dev, vfoState_t state);

      //! Construct the command object to select %VFO mode
      /*!
       * @param   [in] dev The %Icom Device in question
       * @date    September 6, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      VFO(const Device& dev);

      static const uint8_t code=0x07;  //!< Command code
   };
}

#endif
