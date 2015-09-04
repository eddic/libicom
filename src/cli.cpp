#include <string>
#include <deque>
#include <utility>
#include <algorithm>
#include <iostream>
#include <array>
#include <iomanip>
#include <locale>

#include "Device.hpp"
#include "Controller.hpp"
#include "GetFrequency.hpp"

enum Command {
   GETFREQUENCY
};

class InvalidCommand: public std::exception
{
   const char* what() const throw()
   {
      return "Invalid Command.";
   }
};

typedef std::array<std::string, 1> CommandStrings;
const CommandStrings commandStrings = {
      "getfrequency"};

int main(int argc, char *argv[])
{
   try
   {
      std::deque<std::string> arguments;

      for(int i=1; i<argc; ++i)
         arguments.push_back(std::string(argv[i]));

      if(arguments.size() < 4)
         throw;

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
      const unsigned char deviceAddress = (unsigned char)std::stoi(
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

      std::cout.imbue(std::locale(""));

      switch(commandID)
      {
         case GETFREQUENCY:
         {
            Icom::Command command(Icom::GetFrequency::make(device));
            const Icom::GetFrequency& getFrequency=
               *static_cast<const Icom::GetFrequency*>(command.get());

            controller.execute(command);
            std::cout << "Operating frequency: "
                      << std::fixed << getFrequency.result()
                      << std::endl;
            break;
         }
         default:
            throw InvalidCommand();
      }

      return 0;
   }
   catch(std::exception& e)
   {
      std::cerr << "Error: " << e.what() << std::endl;
      return 1;
   }
}
