#include "Sine.hpp"
#include <cmath>


#include <exception>

Sine::Sine(unsigned int &sampleRate, float frqz, float offset, float attack, float hold, float decay) : Lyr(sampleRate)
{
  m_Sample = new float[m_SampleSize];
  try
  {
    auto m = [=](float x)->float{
      //std::cout << x << " ";
      if(x < offset)
      {
        return 0;
      }
      else if(x < (offset + attack))
      {
        return 1.0 / attack * (x - offset);
      }
      else if (x < (offset + attack + hold))
      {
        return 1.0;
      }
      else if(x < (offset + attack + hold + decay))
      {
        return 1.0 - (1.0 / decay) * (x - (offset + attack + hold));
      }
      else
      {
        return 0.0;
      }
    };

    float w = (2*M_PI*frqz)/m_SampleSize;

    for (size_t i = 0; i < m_SampleSize; i++) {
      m_Sample[i] = sin(w*i)*m(static_cast<float>(i)/m_SampleSize);

      //std::cout << m_Sample[i] << std::endl;
    }

    //char p;
    //std::cin >> p;

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
    *buffer += m_Sample[m_SamplePos];
    *buffer /= 2;
    buffer++;
    m_SamplePos++;

    if(m_SamplePos >= m_SampleSize)
    {
      m_SamplePos = 0;
    }
  }
}
