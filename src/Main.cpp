#include <fmsynth.h>
#include <iostream>

#include <alsa/asoundlib.h>

#include "ISnd.hpp"

static unsigned int SAMPLE_RATE = 44100;

static size_t FRAME_COUNT = 8096;

int main() {

  std::cout << "Start up!" << std::endl;

  ISnd* snd = new ISnd(SAMPLE_RATE);

  float* lBuffer = new float[FRAME_COUNT];
  float* rBuffer = new float[FRAME_COUNT];

  fmsynth_t* fm = fmsynth_new(SAMPLE_RATE, 1);
  fmsynth_note_on(fm, 80, 20);

  fmsynth_render(fm, lBuffer, rBuffer, FRAME_COUNT);

  snd->PlayBuffers(lBuffer, rBuffer, FRAME_COUNT);

  fmsynth_release_all(fm);
  fmsynth_free(fm);

  std::cout << "Shut down!" << std::endl;
  delete snd;
  return 0;
}
