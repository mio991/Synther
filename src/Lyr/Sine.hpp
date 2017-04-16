#pragma once

#include "../Lyr.hpp"

class Sine : public Lyr {
public:
  Sine (unsigned int &sampleRate, float frqz, float offset, float attack, float hold, float decay);
  virtual ~Sine();

  void AddLayer(float* buffer, size_t size);
private:
  float* m_Sample;

  size_t m_SamplePos = 0;
};
