#pragma once

#include <cstdlib>
#include <iostream>

class Lyr {
public:
  Lyr(unsigned int &sampleRate);
  virtual void AddLayer(float* buffer, size_t size) = 0;

protected:
  unsigned int &m_SampleRate;
  size_t m_SampleSize;
};
