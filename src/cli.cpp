#include <string>
#include <deque>
#include <utility>
#include <algorithm>
#include <iostream>
#include <array>
#include <iomanip>
#include <locale>
#include <sstream>

#include "Device.hpp"
#include "Controller.hpp"
#include "Frequency.hpp"

enum Command {
   FREQUENCY
};

typedef std::array<std::string, 1> CommandStrings;
const CommandStrings commandStrings = {
      "frequency"};

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
      const Icom::ModelNames::const_iterator modelName = std::find(
            Icom::modelNames.cbegin(),
            Icom::modelNames.cend(),
            arguments.front());
      arguments.pop_front();
      if(modelName == Icom::modelNames.cend())
         throw;
      const Icom::Model model =
         (Icom::Model)(modelName-Icom::modelNames.cbegin());

      // Third should be the device address
      if(arguments.front().size() != 2)
         throw;
      const unsigned char deviceAddress = (unsigned char)std::stoul(
            arguments.front(),
            0,
            16);
      arguments.pop_front();

      // Now we make the device object
      const Icom::Device device({model, deviceAddress});

      // Fourth should be our command
      const Command commandID = (Command)(
            std::find(
               commandStrings.cbegin(),
               commandStrings.cend(),
               arguments.front())
            -commandStrings.cbegin());
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
