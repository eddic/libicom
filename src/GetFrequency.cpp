#include "GetFrequency.hpp"

void Icom::GetFrequency::subComplete()
{
   if(*resultStart() == 0x03)
   {
      unsigned int multiplier=1;
      m_frequency=0;
      for(auto number = resultStart()+1; number != resultEnd(); ++number)
      {
         m_frequency += (*number&0x0f)*(multiplier);
         multiplier *= 10;
         m_frequency += (*number>>4)*(multiplier);
         multiplier *= 10;
      }
      m_status = SUCCESS;            
   }
}

Icom::GetFrequency::GetFrequency(
      unsigned char destination,
      unsigned char source):
   Command_base(1, 1+5, destination, source),
   m_frequency(0)
{
   *m_commandStart() = 0x03;
}
