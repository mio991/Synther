#include "Drctr.hpp"

#include "Lyr/Sine.hpp"


void Drctr::AddLayer(float* buffer, size_t size)
{
  for(size_t i = 0; i < m_Layers.size(); i++)
  {
    m_Layers[i]->AddLayer(buffer, size);
  }
}

Drctr::Drctr(unsigned int &sampleRate) : Lyr(sampleRate)
{
  std::cout << "Create Director!" << std::endl;

  m_Layers.push_back(new Sine(m_SampleRate, 288+144, 0.25, 0.1, 0.2, 0.35));
  m_Layers.push_back(new Sine(m_SampleRate, 144, 0, 0.025, 0.1, 0.05));
}

Drctr::~Drctr()
{
}
