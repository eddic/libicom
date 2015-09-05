/*!
 * @file       Controller.hpp
 * @brief      Declares the Icom::Controller class
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

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <exception>
#include <string>

#include "Command.hpp"

//! Contains all elements for controlling %Icom devices
namespace Icom
{
   //! Class for representing an %Icom CI-V controller
   /*!
    * @date    September 4, 2015
    * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
    */
   class Controller
   {
   public:
      //! Sole constructor
      /*!
       * @param   [in] port The string representation of the serial port.
       * @param   [in] baudrate The baud rate to operate the serial port at.
       */
      Controller(
            const std::string& port,
            unsigned int baudRate=19200,
            uint8_t address=0xe0);

      ~Controller();

      //! Synchronously execute a command
      /*!
       * This returns once the command has completed its execution. The commands
       * result and status are set following this.
       *
       * @param   [inout] command The Command to execute.
       */
      void execute(Command& command) const;

      class CantOpenPort: public std::exception
      {
         const char* what() const throw()
         {
            return "Unable to open serial port.";
         }
      };

      class PortNotTTY: public std::exception
      {
         const char* what() const throw()
         {
            return "Serial port is not a tty.";
         }
      };

      class InvalidBaudRate: public std::exception
      {
         const char* what() const throw()
         {
            return "Invalid baud rate.";
         }
      };

      class InvalidReply: public std::exception
      {
         const char* what() const throw()
         {
            return "Invalid reply from device.";
         }
      };

      class BufferOverflow: public std::exception
      {
         const char* what() const throw()
         {
            return "Receive buffer would overflow.";
         }
      };

      class WriteError: public std::exception
      {
         const char* what() const throw()
         {
            return "Error writing to serial port.";
         }
      };

      class ReadError: public std::exception
      {
         const char* what() const throw()
         {
            return "Error reading from serial port.";
         }
      };

   private:
      int m_fd;  //!< File descriptor of serial port.

      //! Retrieve a byte from the serial port
      inline uint8_t get() const;

      //! Send a string of bytes down the serial port
      inline void put(const Buffer data) const;

      //! Send a byte down the serial port
      inline void put(const uint8_t byte) const;

      //! Address of controller
      const uint8_t m_address;
   };
}

#endif
