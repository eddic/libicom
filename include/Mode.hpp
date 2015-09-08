/*!
 * @file       Mode.hpp
 * @brief      Declares the classes for setting/getting the operating
 *             mode of an %Icom device.
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

#ifndef MODE_HPP
#define MODE_HPP

#include "libicom/command.hpp"

//! Contains all elements for controlling %Icom devices
namespace Icom
{
   enum mode_t: uint8_t
   {
      LSB   = 0x00,
      USB   = 0x01,
      AM    = 0x02,
      CW    = 0x03,
      FSK   = 0x04,
      FM    = 0x05,
      WFM   = 0x06,
      CWR   = 0x07,
      FSKR  = 0x08,
      SAMD  = 0x11,
      PSK   = 0x12,
      SAML  = 0x14,
      SAMU  = 0x15,
      P25   = 0x16
   };
   typedef std::array<std::string, 0x17> modeNames_t;
   extern const modeNames_t modeNames;
   STRING_TO_ENUM(mode)

   enum filter_t: uint8_t
   {
      NONE   = 0x00,
      WIDE   = 0x01,
      MEDIUM = 0x02,
      NARROW = 0x03
   };
   typedef std::array<std::string, 0x04> filterNames_t;
   extern const filterNames_t filterNames;
   STRING_TO_ENUM(filter)

   //! Retrieve the operating mode of an %Icom CI-V device
   /*!
    * @date    September 8, 2015
    * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
    */
   class GetMode: public Command_base
   {
   public:
      //! Complete the command
      /*!
       * Calling this function forces the child class to process the result data
       * buffer into the actual operating mode.
       *
       * @return  Always true.
       * @date    September 4, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      bool subcomplete();

      //! Retrieve the operating mode
      /*!
       * The output of this function is only valid once subcomplete() has been
       * called.
       *
       * @return  Current operating mode of device
       * @date    September 3, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      mode_t mode() const { return m_mode; }

      //! Retrieve the filter width
      /*!
       * The output of this function is only valid once subcomplete() has been
       * called.
       *
       * @return  Current filter width of device
       * @date    September 3, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      filter_t filter() const { return m_filter; }

      //! Make a command object
      /*!
       * @param   [in] dev The %Icom device in question
       * @date    September 8, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      static GetMode* make(const device_t& dev)
      {
         return new GetMode(dev);
      }
       
   private:
      //! Construct the command object
      /*!
       * @param   [in] dev The %Icom device in question
       * @date    September 8, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      GetMode(const device_t& dev);

      static const uint8_t code=0x04;  //!< Command code

      mode_t m_mode;  //!< Operating mode
      filter_t m_filter;  //!< filter_t width
   };

   //! Set the operating mode of an %Icom CI-V device
   /*!
    * @date    September 8, 2015
    * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
    */
   class SetMode: public Command_base
   {
   public:
      //! Make a command object
      /*!
       * @param   [in] dev The %Icom device in question
       * @param   [in] mode The desired operating mode
       * @param   [in] filter The desired filter width
       * @date    September 8, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      static SetMode* make(
            const device_t& dev,
            mode_t mode,
            filter_t filter)
      {
         return new SetMode(dev, mode, filter);
      }
       
   private:
      //! Construct the command object
      /*!
       * @param   [in] dev The %Icom device in question
       * @param   [in] mode The desired operating mode
       * @param   [in] filter The desired filter width
       * @date    September 8, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      SetMode(
            const device_t& dev,
            mode_t mode,
            filter_t filter);

      static const uint8_t code=0x06;  //!< Command code
   };
}

#endif
