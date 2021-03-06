#include "Lyr.hpp"

Lyr::Lyr(unsigned int &sampleRate) : m_SampleRate(sampleRate)
{
  std::cout << "Create Layer!" << std::endl;
  m_SampleSize = static_cast<size_t>((4.0 * m_SampleRate)/3.0);
}
