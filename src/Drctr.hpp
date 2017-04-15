#pragma once

#include "Lyr.hpp"

#include <functional>

class Drctr : public Lyr {
public:
  Drctr(size_t sampleRate);
  virtual ~Drctr();

  void AddLayer(float* buffer, size_t size);

private:
  Lyr** m_Layers;
  size_t m_LayerCount;

  void forEachLayer(std::function<void (Lyr*)> &f);
  void add(Lyr* lyr);
};
