/*!
 * @file       command.hpp
 * @brief      Declares a base class for handling CI-V commands
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

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <vector>
#include <memory>

#include "Device.hpp"

//! Contains all elements for controlling %Icom devices
namespace Icom
{
   //! Container type for command and result buffers
   typedef std::vector<uint8_t> Buffer;

   //! Enumeration for indicating command status
   enum Status {INCOMPLETE, FAIL, PARSEERROR, SUCCESS};

   //! Base class for handling %Icom CI-V commands
   /*!
    * This class should be derived from to implement any %Icom CI-V control
    * commands.
    *
    * @date    September 8, 2015
    * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
    */
   class Command_base
   {
   public:
      //! Retrieve command buffer
      /*!
       * @return  Constant reference command data buffer.
       * @date    September 1, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      const Buffer& commandData() const
      {
         return m_command;
      }

      //! Retrieve buffer for command result data
      /*!
       * @return  Reference to command result data buffer.
       * @date    September 1, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      Buffer& resultData()
      {
         return m_result;
      }

      //! Check status of command
      /*!
       * @return  Current status of command
       * @date    September 1, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      Status status() const { return m_status; }

      virtual ~Command_base() {}

      static const uint8_t footer=0xfd;  //!< Byte indicating message end
      static const uint8_t header=0xfe;  //!< Byte indicating message start
      static const size_t bufferReserveSize=64;  //!< Size of command/result buffer reserve
      const Device device;  //!< Target %Icom device

      //! Initiate completion
      /*!
       * Calling this function forces the class to process the result data
       * buffer. Normally just returns "true".
       *
       * We also use this function for commands that may require multiple
       * executions before they are actually complete. One example of this
       * being useful is for polling the squelch status of the receiver and not
       * being "done" until it is either open or close.
       *
       * @return  "false" if command should be run again. "true" otherwise.
       * @date    September 4, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      bool complete();

      const bool m_reply;
   protected:
      //! %Command specific completion
      /*!
       * Calling this function forces the child class to process the result
       * data buffer. Normally just return "true".
       *
       * We also use this virtual function for commands that may require
       * multiple executions before they are actually complete. One example of
       * this being useful is for polling the squelch status of the receiver
       * and not being "done" until it is either open or close.
       *
       * @return  "false" if command should be run again. "true" otherwise.
       * @date    September 4, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      virtual bool subcomplete() { return true; }

      //! Sole constructor
      /*!
       * @param   [in] dev The %Icom %Device in question
       * @param   [in] reply Should we expect a reply?
       * @date    September 3, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      Command_base(const Device& dev, bool reply=true);

      Status m_status;   //!< Current status of command
      Buffer m_command;  //!< Buffer with command data
      Buffer m_result;   //!< Buffer with command result
   };

   //! Shared pointer holder for commands.
   typedef std::shared_ptr<Command_base> Command;
}

#endif
