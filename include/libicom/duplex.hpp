/*!
 * @file       duplex.hpp
 * @brief      Declares the classes for setting/getting the duplex duplex and 
 *             offset of an %Icom device.
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

#ifndef DUPLEX_HPP
#define DUPLEX_HPP

#include "libicom/command.hpp"

//! Contains all elements for controlling %Icom devices
namespace Icom
{
   //! Retrieve the duplex offset of an %Icom CI-V device
   /*!
    * @date    September 21, 2015
    * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
    */
   class GetDuplex: public Command_base
   {
   public:
      //! Complete the command
      /*!
       * Calling this function forces the child class to process the result data
       * buffer into the actual duplex offset.
       *
       * @return  Always true.
       * @date    September 21, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      bool subcomplete();

      //! Retrieve the duplex offset
      /*!
       * The output of this function is only valid once subcomplete() has been
       * called.
       *
       * @return  Current duplex offset of device
       * @date    September 21, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      int offset() const { return m_offset; }

      //! Make a command object
      /*!
       * @param   [in] dev The %Icom device in question
       * @date    September 21, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      static GetDuplex* make(const device_t& dev)
      {
         return new GetDuplex(dev);
      }
       
   private:
      //! Construct the command object
      /*!
       * @param   [in] dev The %Icom device in question
       * @date    September 21, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      GetDuplex(const device_t& dev);

      static const uint8_t code=0x0c;  //!< Command code

      int m_offset;  //!< Duplex offset
   };

   //! Set the operating duplex of an %Icom CI-V device
   /*!
    * @date    September 21, 2015
    * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
    */
   class SetDuplex: public Command_base
   {
   public:
      //! Make a command object
      /*!
       * @param   [in] dev The %Icom device in question
       * @param   [in] offset The desired duplex offset. Zero to disable.
       * @date    September 21, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      static SetDuplex* make(
            const device_t& dev,
            int offset)
      {
         return new SetDuplex(dev, offset);
      }

      //! Complete the command
      /*!
       * Calling this command loads up the second command on the first call.
       * Returns true on the second call.
       *
       * @return  True on second call. False on first.
       * @date    September 21, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      bool subcomplete();

       
   private:
      //! Construct the command object
      /*!
       * @param   [in] dev The %Icom device in question
       * @param   [in] offset The desired duplex offset. Zero to disable.
       * @date    September 21, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      SetDuplex(
            const device_t& dev,
            int offset);

      static const uint8_t offset_code=0x0d; //!< Code to set offset
      static const uint8_t mode_code=0x0f;   //!< Code to set duplex mode

      bool m_started;

      const int m_offset;
   };
}

#endif
