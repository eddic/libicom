/*!
 * @file       Command.hpp
 * @brief      Declares the Icom::Command class
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

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <vector>
#include <memory>

//! Contains all elements for controlling %Icom devices
namespace Icom
{
   //! Container type for command and result buffers
   typedef std::vector<unsigned char> Buffer;

   //! Enumeration for indicating command status
   enum Status {INCOMPLETE, FAIL, SUCCESS};

   //! Base class for any %Icom CI-V commands
   /*!
    * This class should be derived from to implement any %Icom CI-V control
    * commands.
    *
    * @date    September 2, 2015
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

      //! Complete the command
      /*!
       * Calling this initiates the processing of the result data buffer.
       *
       * @date    September 1, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      void complete();

      //! Check status of command
      /*!
       * @return  Current status of command
       * @date    September 1, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      Status status() const { return m_status; }

      virtual ~Command_base() {}

      static const unsigned char footer=0xfd;
      static const unsigned char header=0xfe;
      static const size_t bufferReserveSize=64;
      const unsigned char m_destination;  //!< Address of destination device
      const unsigned char m_source;       //!< Address of source device
   protected:
      //! Sole constructor
      /*!
       * @param   [in] destination The CI-V address of the destination device.
       * @param   [in] source The CI-V address of the source controller.
       * @date    September 2, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      Command_base(
            const unsigned char destination,
            const unsigned char source);

      Status m_status;                    //!< Current status of command

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
       * @date    September 1, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      virtual bool complete() =0;

      Buffer m_command;  //!< Buffer with actual command data
      Buffer m_result;   //!< Buffer with command result
   };

   //! Shared pointer holder for commands.
   typedef std::shared_ptr<Command_base> Command;
}

#endif
