/*!
 * @file       VFO.hpp
 * @brief      Declares classes for selecting and modifying %VFO mode
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

#ifndef VFO_HPP
#define VFO_HPP

#include "libicom/command.hpp"

//! Contains all elements for controlling %Icom devices
namespace Icom
{
   enum vfoState_t: uint8_t
   {
      VFOA     = 0x00,
      VFOB     = 0x01,
      SWAP     = 0xb0,
      SINGLE   = 0xc0,
      DUAL     = 0xc1
   };
   typedef std::array<std::string, 0xc2> vfoStateNames_t;
   extern const vfoStateNames_t vfoStateNames;
   STRING_TO_ENUM(vfoState)

   //! Base class selecting or configuring VFO mode
   /*!
    * @date    September 8, 2015
    * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
    */
   class VFO: public Command_base
   {
   public:
      //! Make a command object to set the %VFO state
      /*!
       * @param   [in] dev The %Icom device in question
       * @param   [in] state What state do we want to put the %VFO in?
       * @date    September 8, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      static VFO* make(const device_t& dev, vfoState_t state)
      {
         return new VFO(dev, state);
      }

      //! Make a command object to select %VFO mode
      /*!
       * @param   [in] dev The %Icom device in question
       * @date    September 8, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      static VFO* make(const device_t& dev)
      {
         return new VFO(dev);
      }
   private:
      //! Construct the command object to set the %VFO state
      /*!
       * @param   [in] dev The %Icom device in question
       * @param   [in] state What state do we want to put the %VFO in?
       * @date    September 8, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      VFO(const device_t& dev, vfoState_t state);

      //! Construct the command object to select %VFO mode
      /*!
       * @param   [in] dev The %Icom device in question
       * @date    September 8, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      VFO(const device_t& dev);

      static const uint8_t code=0x07;  //!< Command code
   };
}

#endif
