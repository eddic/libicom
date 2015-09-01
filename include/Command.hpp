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

//! Contains all elements for controlling Icom devices
namespace Icom
{
   enum Status {INCOMPLETE, FAIL, SUCCESS};

   //! Base class for any Icom CI-V commands
   /*!
    * This class should be derived from to implement any Icom CI-V control
    * commands.
    *
    * @date    September 1, 2015
    * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
    */
   class Command_base
   {
   public:
      typedef std::vector<unsigned char> Buffer;

      //! Retrieve command buffer
      /*!
       * @return  Constant reference to vector of command data string.
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
       * Calling this function forces a process of the result data buffer.
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
      Command_base(
            size_t commandSize,
            size_t resultSize,
            unsigned char destination,
            unsigned char source);

      Status m_status;              //!< Current status of command
      unsigned char m_destination;  //!< Address of destination device
      unsigned char m_source;       //!< Address of source device
      const size_t headerSize=4;    //!< Size of header in bytes
      const size_t footerSize=1;    //!< Size of footer in bytes

      Buffer::iterator commandStart()
      {
         return m_command.begin()+headerSize;
      }

      Buffer::iterator commandEnd()
      {
         return m_command.end()-footerSize;
      }

      Buffer::const_iterator resultStart() const
      {
         return m_result.cbegin()+headerSize;
      }

      Buffer::const_iterator resultEnd() const
      {
         return m_result.cend()-footerSize;
      }

      //! %Command specific completion
      /*!
       * Calling this function forces the childc class to process the result
       * data buffer.
       *
       * @date    September 1, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      void subComplete() =0;

   private:
      Buffer m_command;             //!< Buffer with actual command data
      Buffer m_result;              //!< Buffer with command result
   };

   typedef std::shared_ptr<Command_base> Command;
}

#endif
