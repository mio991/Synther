#include "Drctr.hpp"

#include "Lyr/Sine.hpp"


void Drctr::AddLayer(float* buffer, size_t size)
{
  std::function<void (Lyr*)> f = [&](Lyr* lyr) {
    lyr->AddLayer(buffer, size);
  };
  forEachLayer(f);
}

Drctr::Drctr(size_t sampleRate) : Lyr(sampleRate)
{
  std::cout << "Create Director!" << std::endl;
  m_LayerCount = 0;
  m_Layers = new Lyr*[10];

  add(new Sine(m_SampleRate, 144, 0, 0.015, 0.175, 0.35));
}

Drctr::~Drctr()
{
  delete m_Layers;
}

void Drctr::forEachLayer(std::function<void (Lyr*)> &f)
{
  for(Lyr** lyrPtr = m_Layers; lyrPtr != NULL; lyrPtr++)
  {
    f(*lyrPtr);
  }
}

void Drctr::add(Lyr* lyr)
{
  m_Layers[m_LayerCount] = lyr;

  m_LayerCount++;
}
