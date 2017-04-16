#pragma once

#include <alsa/asoundlib.h>

class ISnd{
public:
  ISnd(unsigned int &sampleRate, float volMultiplier = 1);
  void Start();
  void PlayBuffers(float* Buffer);
  size_t getFrameCount();
  unsigned int &getSampleRate();
  ~ISnd();

private:
  snd_pcm_t *h_pb;
  size_t frameCount;
  float volMultiplier;

  unsigned int &m_SampleRate;

  void interleave(float* lBuffer, float* rBuffer, float* buf);
};
