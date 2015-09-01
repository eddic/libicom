#include "Command.hpp"

void Icom::Command_base::complete()
{
   if(
         m_result[0] == 0xfe &&
         m_result[1] == 0xfe &&
         m_result[2] == m_source &&
         m_result[3] == m_destination &&
         m_result.back() == 0xfd)
      subComplete();

   if(m_status != SUCCESS)
      m_status = FAIL;
}

Icom::Command_base(
      size_t commandSize,
      size_t resultSize,
      unsigned char destination,
      unsigned char source):
   m_command(commandSize+headerSize+footerSize, 0),
   m_result(resultSize+headerSize+footerSize, 0),
   m_status(INCOMPLETE),
   m_destination(destination),
   m_source(source)
{
   m_command[0] = 0xfe;
   m_command[1] = 0xfe;
   m_command[2] = m_destination;
   m_command[3] = m_source;
   m_command.back() = 0xfd;
}
