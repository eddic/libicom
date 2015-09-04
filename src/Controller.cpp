/*!
 * @file       Controller.cpp
 * @brief      Defines the Icom::Controller class
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

#include "Controller.hpp"

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

Icom::Controller::Controller(
      const std::string& port,
      unsigned int baudRate,
      unsigned char address):
   m_fd(-1),
   m_address(address)
{
   m_fd = open(port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
   if(m_fd == -1)
      throw CantOpenPort();

   fcntl(m_fd, F_SETFL, 0);
   if (!isatty(m_fd))
   {
      close(m_fd);
      m_fd=-1;
      throw PortNotTTY();
   }
   
   // Configure serial port options
   struct termios options;
   tcgetattr(m_fd, &options);

   // Set serial port speed
   speed_t rate=B0;
   switch(baudRate)
   {
      case 300:
         rate=B300;
         break;
      case 1200:
         rate=B1200;
         break;
      case 2400:
         rate=B2400;
         break;
      case 4800:
         rate=B4800;
         break;
      case 9600:
         rate=B9600;
         break;
      case 19200:
         rate=B19200;
         break;
      default:
         InvalidBaudRate();
   }
   cfsetispeed(&options, rate);
   cfsetospeed(&options, rate);

   // Set serial port options
   options.c_lflag &= ~(
         ICANON | ECHO | ECHOE | ISIG | OPOST |  // We want raw mode
         IXON | IXOFF | IXANY |                  // No software flow control
         CSIZE |                                 // We set it to 8 bits below
         PARENB |                                // No parity bits
         CSTOPB |                                // Single stop bit
         // CNEW_RTSCTS |                           // No hardware flow control
         HUPCL                                   // Don't mess with the DTR
         );
   options.c_cflag |= (CLOCAL | CREAD | CS8 | IGNPAR);
   options.c_cc[VTIME] = 2;                      // Timeout our reads in 200ms
   options.c_cc[VMIN] = 0;
   tcsetattr(m_fd, TCSANOW, &options);

   // Enable the DTR
   int lineData;
   ioctl(m_fd, TIOCMGET, &lineData);
   lineData |= TIOCM_DTR;
   ioctl(m_fd, TIOCMSET, &lineData);
}

Icom::Controller::~Controller()
{
   if(m_fd != -1)
   {
      int lineData;
      ioctl(m_fd, TIOCMGET, &lineData);
      lineData &= ~TIOCM_DTR;
      ioctl(m_fd, TIOCMSET, &lineData);
      close(m_fd);
   }
}

void Icom::Controller::execute(Command& command) const
{
   bool notForUs=false;

   do
   {
      // Send the command
      const Buffer header={
            Command_base::header,
            Command_base::header,
            command->device.address,
            m_address};
      put(header);
      put(command->commandData());
      put(Command_base::footer);

      // Get the reply
      unsigned int state=0;
      unsigned char buffer;
      while(state<5)
      {
         buffer=get();

         switch(state)
         {
            case 0:
            case 1:
               if(buffer!=Command_base::header)
                  throw;
               ++state;
               break;
            case 2:
               if(buffer!=m_address)
                  notForUs=true;
               ++state;
               break;
            case 3:
               if(buffer!=command->device.address)
                  notForUs=true;
               ++state;
               break;
            case 4:
               if(buffer != Command_base::footer)
                  command->resultData().push_back(buffer);
               else
                  ++state;
               break;
         }

         // We don't want to recieve a giant reply
         if(command->resultData().size() >= Command_base::bufferReserveSize)
            throw;
      }

   } while(notForUs || !command->complete());
}

unsigned char Icom::Controller::get() const
{
   unsigned char x;
   ssize_t n=0;
   while(n==0)
      n = read(m_fd, &x, 1);
   if(n < 0)
      throw;
   return x;
}

void Icom::Controller::put(const Buffer data) const
{
   size_t position=0;
   ssize_t n;
   while(position < data.size())
   {
      n = write(
            m_fd, 
            &data.front()+position,
            data.size()-position);
      if(n < 0)
         throw;
      position += n;
   }
}

void Icom::Controller::put(const unsigned char byte) const
{
   ssize_t n=0;
   while(n==0)
      n = write(m_fd, &byte, 1);
   if(n < 0)
      throw;
}
