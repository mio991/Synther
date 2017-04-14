#pragma once

#include <alsa/asoundlib.h>

class ISnd{
public:
  ISnd(unsigned int sampleRate);
  void Start();
  void PlayBuffers(float* lBuffer, float* rBuffer);
  size_t getFrameCount();
  ~ISnd();

private:
  snd_pcm_t *h_pb;
  void** bufs;
  size_t frameCount;

  void interleave(float* lBuffer, float* rBuffer, float* buf);
};
