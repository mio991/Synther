#pragma once

#include <alsa/asoundlib.h>

class ISnd{
public:
  ISnd(unsigned int sampleRate);
  void PlayBuffers(float* lBuffer, float* rBuffer, size_t frameCount);
  ~ISnd();

private:
  snd_pcm_t *h_pb;
  void** bufs;

};
