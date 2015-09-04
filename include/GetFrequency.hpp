/*!
 * @file       GetFrequency.hpp
 * @brief      Declares the Icom::GetFrequency class
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

#ifndef GETFREQUENCY_HPP
#define GETFREQUENCY_HPP

#include <vector>

#include "Command.hpp"

//! Contains all elements for controlling %Icom devices
namespace Icom
{
   //! Retrieve the operating frequency of an %Icom CI-V device
   /*!
    * @date    September 3, 2015
    * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
    */
   class GetFrequency: public Command_base
   {
   public:
      //! Complete the command
      /*!
       * Calling this function forces the child class to process the result data
       * buffer into the actual operating frequency.
       *
       * @return  Always true.
       * @date    September 2, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      bool subcomplete();

      //! Retrieve the operating frequency
      /*!
       * The output of this function is only valid once subcomplete() has been
       * called.
       *
       * @return  Integer representation of operating frequency in Hertz.
       * @date    September 3, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      unsigned int result() const { return m_frequency; }

      static GetFrequency* make(const Device& dev)
      {
         return new GetFrequency(dev);
      }
       
   private:
      //! Construct the command object
      /*!
       * @param   [in] Device The %Icom Device in question
       * @date    September 2, 2015
       * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
       */
      GetFrequency(const Device& dev);

      unsigned int m_frequency;              //!< Retrieved operating frequency
      static const unsigned char code=0x03;  //!< Command code
   };
}

#endif
