#pragma once

#include <cstdlib>
#include <iostream>

class Lyr {
public:
  Lyr(size_t sampleRate);
  virtual void AddLayer(float* buffer, size_t size) = 0;

protected:
  unsigned long m_SampleRate;
  size_t m_SampleSize;
};
