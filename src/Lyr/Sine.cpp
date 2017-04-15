#include "Sine.hpp"
#include <cmath>


#include <exception>

Sine::Sine(size_t sampleRate, float frqz, float offset, float attack, float hold, float decay) : Lyr(sampleRate)
{
  m_Sample = new float[m_SampleSize];
  try
  {
    auto m = [=](float x)->float{
      if(x < 0)
      {
        return 0;
      }

      if(x < attack)
      {
        return 1.0 / attack;
      }
      else if (x < attack + hold)
      {
        return 1.0;
      }
      else if(x < attack + hold + decay)
      {
        return 1.0 - (1.0 / decay);
      }
      else
      {
        return 0.0;
      }
    };

    for (size_t i = 0; i < m_SampleSize; i++) {
      m_Sample[i] = sin((2*M_PI)/((i+1)+offset))*m(1/(i+1));
    }
  }
  catch(std::exception ex)
  {
    std::cerr << ex.what();
  }
}

Sine::~Sine()
{
  delete[] m_Sample;
}

void Sine::AddLayer(float* buffer, size_t size)
{
  for(;0 < size;size--)
  {
    *buffer = m_Sample[m_SamplePos];
    buffer++;
    m_SamplePos++;

    if(m_SamplePos >= m_SampleSize)
    {
      m_SamplePos = 0;
    }
  }
}
