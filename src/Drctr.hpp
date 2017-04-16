#pragma once

#include "Lyr.hpp"

#include <functional>
#include <vector>

class Drctr : public Lyr {
public:
  Drctr(unsigned int &sampleRate);
  virtual ~Drctr();

  void AddLayer(float* buffer, size_t size);

private:
  std::vector<Lyr*> m_Layers;
};
