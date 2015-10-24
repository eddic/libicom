/*!
 * @file       squelch.hpp
 * @brief      Declares the classes for checking and managing the
 *             squelch of an %Icom device.
 * @author     Eddie Carle &lt;eddie@isatec.ca&gt;
 * @date       September 23, 2015
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

#ifndef SQUELCH_HPP
#define SQUELCH_HPP

#include "libicom/command.hpp"

//! Contains all elements for controlling %Icom devices
namespace Icom
{
    enum squelchState_t: uint8_t
    {
        CLOSED = 0x00,
        OPEN   = 0x01
    };
    typedef std::array<std::string, 2> squelchStateNames_t;
    extern const squelchStateNames_t squelchStateNames;
    STRING_TO_ENUM(squelchState)

    //! Wait for the squelch of an %Icom CI-V device to change
    /*!
     * @date    September 23, 2015
     * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
     */
    class SquelchHold: public Command_base
    {
    public:
        //! Make a command object
        /*!
         * @param   [in] dev The %Icom device in question
         * @param   [in] state The state we should wait for the squelch to be.
         * @date    September 23, 2015
         * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
         */
        static SquelchHold* make(const device_t& dev, squelchState_t state)
        {
            return new SquelchHold(dev, state);
        }
    private:
        //! Construct the command object
        /*!
         * @param   [in] dev The %Icom device in question
         * @param   [in] state The state we should wait for the squelch to be.
         * @date    September 23, 2015
         * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
         */
        SquelchHold(const device_t& dev, squelchState_t state);

        //! Complete the command
        /*!
         * Returns false until the squelch changes to the specified state
         *
         * @return  Always true.
         * @date    September 23, 2015
         * @author  Eddie Carle &lt;eddie@isatec.ca&gt;
         */
        bool subcomplete();

        const squelchState_t m_squelchState;

        static const uint8_t code=0x15;  //!< Command code
        static const uint8_t subCode=0x01;  //!< Subcommand code
    };
}

#endif
