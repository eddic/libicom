/*!
 * @file       Command.hpp
 * @brief      Declares the Icom::Command class
 * @author     Eddie Carle &lt;eddie@isatec.ca&gt;
 * @date       September 1, 2015
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
    * @date    September 1, 2015
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
   protected:
      //! Sole constructor
      /*!
       * @param   [in] commandSize The size, in bytes, of the command. This does
       *                           not include the header and footer components
       *                           as they are handled by this class.
       * @param   [in] resultSize The size, in bytes, of the result. This does
       *                          not include the header and footer components
       *                          as they are handled by this class.
       * @param   [in] destination The CI-V address of the destination device.
       * @param   [in] source The CI-V address of the source controller.
       */
      Command_base(
            const size_t commandSize,
            const size_t resultSize,
            const unsigned char destination,
            const unsigned char source);

      Status m_status;                   //!< Current status of command
      unsigned char m_destination;       //!< Address of destination device
      unsigned char m_source;            //!< Address of source device
      static const size_t headerSize=4;  //!< Size of header in bytes
      static const size_t footerSize=1;  //!< Size of footer in bytes

      //! Starting command iterator for children
      Buffer::iterator commandStart()
      {
         return m_command.begin()+headerSize;
      }

      //! Ending command iterator for children
      Buffer::iterator commandEnd()
      {
         return m_command.end()-footerSize;
      }

      //! Starting result iterator for children
      Buffer::const_iterator resultStart() const
      {
         return m_result.cbegin()+headerSize;
      }

      //! Ending result iterator for children
      Buffer::const_iterator resultEnd() const
      {
         return m_result.cend()-footerSize;
      }

      //! %Command specific completion
      /*!
       * Calling this function forces the child class to process the result
       * data buffer.
       *
       * @date    September 1, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      void subComplete() =0;

      //! Check to see if the command is actually done
      /*!
       * We use this virtual function for commands that may require multiple
       * executions before they are actually complete. One example of this being
       * usefull is for polling the squelch status of the reciever and not being
       * "done" until it is either open or close.
       */
      virtual bool done()
      {
         return true;
      }

   private:
      Buffer m_command;  //!< Buffer with actual command data
      Buffer m_result;   //!< Buffer with command result
   };

   //! Shared pointer holder for commands.
   typedef std::shared_ptr<Command_base> Command;
}

#endif
