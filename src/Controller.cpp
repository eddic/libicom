#include "Controller.hpp"

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

Icom::Controller::Controller(
      const char* port,
      unsigned int baudRate):
   fd(-1)
{
   fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
   if(fd == -1)
   {
      throw;
   }
   fcntl(fd, F_SETFL, 0);
   if (!isatty(port)) 
   {
      close(port);
      fd=-1;
      throw;
   }
   
   // Configure serial port options
   struct termios options;
   tcgetattr(fd, &options);

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
         throw;
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
         CNEW_RTSCTS |                           // No hardware flow control
         HUPCL                                   // Don't mess with the DTR
         );
   options.c_cflag |= (CLOCAL | CREAD | CS8 | IGNPAR);
   options.c_cc[VTIME] = 2;                      // Timeout our reads in 200ms
   options.c_cc[VMIN] = 0;
   tcsetattr(fd, TCSANOW, &options);

   // Enable the DTR
   int lineData;
   ioctl(fd, TIOCMGET, &lineData);
   lineData |= TIOCM_DTR;
   ioctl(fd, TIOCMSET, &lineData);
}

Icom::Controller::~Controller()
{
   if(fd != -1)
   {
      int lineData;
      ioctl(fd, TIOCMGET, &lineData);
      lineData &= ~TIOCM_DTR;
      ioctl(fd, TIOCMSET, &lineData);
      close(fd);
   }
}

void Icom::Controller::Execute(Command& command)
{
   const Buffer& commandBuffer=command->commandData();
   Buffer& resultBuffer=command->resultData();

   do
   {
      ssize_t position=0;
      while(position < commandBuffer.size())
      {
         const ssize_t n = write(
               fd, 
               &commandBuffer.font()+position, 
               commandBuffer.size()-position);
         if(n < 0)
            throw;
         position += n;
      }

      position=0;
      while(position < resultBuffer.size())
      {
         const ssize_t n = read(
               fd,
               &resultBuffer.front+position,
               resultBuffer.size()-position);
         if(n < 0)
            throw;
         position += n;
      }

      command->complete();
   } while(!command->done());
}
