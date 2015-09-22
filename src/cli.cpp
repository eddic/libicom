#include <string>
#include <deque>
#include <utility>
#include <algorithm>
#include <iostream>
#include <array>
#include <iomanip>
#include <locale>
#include <sstream>

#include "libicom/device.hpp"
#include "libicom/controller.hpp"
#include "libicom/frequency.hpp"
#include "libicom/power.hpp"
#include "libicom/mode.hpp"
#include "libicom/vfo.hpp"
#include "libicom/duplex.hpp"

enum command_t {
   FREQUENCY,
   POWER,
   MODE,
   VFO,
   DUPLEX
};

typedef std::array<std::string, 5> commandNames_t;
const commandNames_t commandNames = {
   "frequency",
   "power",
   "mode",
   "vfo",
   "duplex"
};

STRING_TO_ENUM(command)

class InvalidCommand: public std::exception
{
   const char* what() const throw()
   {
      return "Invalid Command.";
   }
};

class CommandIncomplete: public std::exception
{
   const char* what() const throw()
   {
      return "Command not complete.";
   }
};

class CommandFailed: public std::exception
{
   const char* what() const throw()
   {
      return "Command failed.";
   }
};

class CommandParseError: public std::exception
{
public:
   CommandParseError(const Icom::Buffer& buffer)
   {
      std::stringstream ss;
      ss << "Failure parsing reply. Got";
      for(const auto& byte : buffer)
         ss << ' '
            << std::setfill('0')
            << std::setw(2)
            << std::fixed
            << std::hex
            << (int)byte;
      m_message = ss.str();
   }
private:
   std::string m_message;

   const char* what() const throw()
   {
      return m_message.c_str();
   }
};

int main(int argc, char *argv[])
{
   try
   {
      std::deque<std::string> arguments;

      for(int i=1; i<argc; ++i)
         arguments.push_back(std::string(argv[i]));

      if(arguments.size() < 4)
         throw std::invalid_argument("Too few arguments");

      // First should be the port
      const Icom::Controller controller(arguments.front());
      arguments.pop_front();

      // Second should be the device name
      const Icom::model_t model = Icom::modelFromName(arguments.front());
      arguments.pop_front();

      // Third should be the device address
      if(arguments.front().size() != 2)
         throw;
      const uint8_t deviceAddress = (uint8_t)std::stoul(
            arguments.front(),
            0,
            16);
      arguments.pop_front();

      // Now we make the device object
      const Icom::device_t device({model, deviceAddress});

      // Fourth should be our command
      const command_t commandID = commandFromName(arguments.front());
      arguments.pop_front();

      Icom::Command command;

      switch(commandID)
      {
         case FREQUENCY:
         {
            if(!arguments.size())
            {
               command.reset(Icom::GetFrequency::make(device));
               const Icom::GetFrequency& getFrequency=
                  *static_cast<const Icom::GetFrequency*>(command.get());

               controller.execute(command);
               switch(command->status())
               {
                  case Icom::SUCCESS:
                     std::cout << std::fixed
                               << getFrequency.result()
                               << std::endl;
                     break;
                  case Icom::PARSEERROR:
                     throw CommandParseError(command->resultData());

                  case Icom::INCOMPLETE:
                     throw CommandIncomplete();

                  case Icom::FAIL:
                     throw CommandFailed();
               }
               return 0;
            }
            else if(arguments.size()==1)
            {
               const unsigned int frequency=std::stoul(arguments.front());
               command.reset(Icom::SetFrequency::make(device, frequency));
               break;
            }
         }

         case POWER:
            command.reset(Icom::Power::make(
                     device,
                     Icom::powerStateFromName(arguments.front())));
            arguments.pop_front();
            break;

         case MODE:            
         {
            if(!arguments.size())
            {
               command.reset(Icom::GetMode::make(device));
               const Icom::GetMode& getmode_t=
                  *static_cast<const Icom::GetMode*>(command.get());

               controller.execute(command);
               switch(command->status())
               {
                  case Icom::SUCCESS:
                     std::cout << Icom::modeNames[(uint8_t)getmode_t.mode()]
                               << '\n'
                               << Icom::filterNames[(uint8_t)getmode_t.filter()]
                               << std::endl;
                     break;
                  case Icom::PARSEERROR:
                     throw CommandParseError(command->resultData());

                  case Icom::INCOMPLETE:
                     throw CommandIncomplete();

                  case Icom::FAIL:
                     throw CommandFailed();
               }
               return 0;
            }
            else if(arguments.size()==1 || arguments.size()==2)
            {
               const Icom::mode_t mode=Icom::modeFromName(arguments.front());
               arguments.pop_front();
               Icom::filter_t filter(Icom::filter_t::NONE);
               if(arguments.size())
               {
                  filter=Icom::filterFromName(arguments.front());
                  arguments.pop_front();
               }
               command.reset(Icom::SetMode::make(device, mode, filter));
               break;
            }
         }

         case VFO:
         {
            if(!arguments.size())
            {
               command.reset(Icom::VFO::make(device));
               break;
            }
            else if(arguments.size()==1)
            {
               command.reset(Icom::VFO::make(
                        device,
                        Icom::vfoStateFromName(arguments.front())));
               break;
            }
         }

         case DUPLEX:
         {
            if(!arguments.size())
            {
               command.reset(Icom::GetDuplex::make(device));
               const Icom::GetDuplex& getDuplex=
                  *static_cast<const Icom::GetDuplex*>(command.get());

               controller.execute(command);
               switch(command->status())
               {
                  case Icom::SUCCESS:
                     std::cout << std::fixed
                               << getDuplex.offset()
                               << std::endl;
                     break;
                  case Icom::PARSEERROR:
                     throw CommandParseError(command->resultData());

                  case Icom::INCOMPLETE:
                     throw CommandIncomplete();

                  case Icom::FAIL:
                     throw CommandFailed();
               }
               return 0;
            }
            else if(arguments.size()==1)
            {
               const int offset=std::stoi(arguments.front());
               command.reset(Icom::SetDuplex::make(device, offset));
               break;
            }
         }

         default:
            throw InvalidCommand();
      }

      controller.execute(command);
      switch(command->status())
      {
         case Icom::SUCCESS:
            std::cout << "Command Succeeded" << std::endl;
            break;
         case Icom::PARSEERROR:
            throw CommandParseError(command->resultData());

         case Icom::INCOMPLETE:
            throw CommandIncomplete();

         case Icom::FAIL:
            throw CommandFailed();
      }

      return 0;
   }
   catch(std::exception& e)
   {
      std::cerr << "Error: " << e.what() << std::endl;
      return 1;
   }
}
