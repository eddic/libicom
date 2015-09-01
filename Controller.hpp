/*!
 * @file       Controller.hpp
 * @brief      Declares the Icom::Controller class
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

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Command.hpp"

//! Contains all elements for controlling Icom devices
namespace Icom
{
   //! Class for controlling Icom devices via CI-V
   /*!
    * @date    September 1, 2015
    * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
    */
   class Controller
   {
   public:
      Controller(
            const char* port,
            unsigned int baudRate=19200);

      ~Controller();

      //! Execute a command from this controller to a CI-V device
      /*!
       * @param   [inout] command Reference to command to execute
       * @date    September 1, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      void Execute(Command& command);

   private:
      int m_fd;   //!< File descriptor of serial port
   };
}

#endif
