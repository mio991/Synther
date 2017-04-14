#pragma once

#include <alsa/asoundlib.h>

class ISnd{
public:
  ISnd(unsigned int sampleRate, float volMultiplier = 1);
  void Start();
  void PlayBuffers(float* lBuffer, float* rBuffer);
  size_t getFrameCount();
  ~ISnd();

private:
  snd_pcm_t *h_pb;
  void** bufs;
  size_t frameCount;
  float volMultiplier;

  void interleave(float* lBuffer, float* rBuffer, float* buf);
};
