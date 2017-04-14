#include <fmsynth.h>
#include <iostream>
#include <algorithm>

#include <cstdlib>

#include <alsa/asoundlib.h>

#include "ISnd.hpp"

static unsigned int SAMPLE_RATE = 44100;

int main(int argc, char const *argv[]) {

  int frqz = 80;
  int attack = 10;
  int loops = 24;
  float volMultiplier = 1;

  if(argc > 1)
  {
    frqz = atoi(argv[1]);
  }

  if(argc > 2)
  {
    attack = atoi(argv[2]);
  }

  if(argc > 3)
  {
    loops = atoi(argv[3]);
  }

  if(argc > 4)
  {
    volMultiplier = atof(argv[4]);
  }

  std::cout << "Start up!" << std::endl;

  ISnd* snd = new ISnd(SAMPLE_RATE, volMultiplier);

  std::cout << "Frame Count: " << snd->getFrameCount() << std::endl;

  float* lBuffer = new float[snd->getFrameCount()];
  float* rBuffer = new float[snd->getFrameCount()];

  fmsynth_t* fm = fmsynth_new(SAMPLE_RATE, 1);
  fmsynth_note_on(fm, frqz, attack);


  for(int i = 0; i < loops; i++){

    std::fill(lBuffer, lBuffer + snd->getFrameCount(), 0);
    std::fill(rBuffer, rBuffer + snd->getFrameCount(), 0);

    fmsynth_render(fm, lBuffer, rBuffer, snd->getFrameCount());
    snd->PlayBuffers(lBuffer, rBuffer);

  }

  fmsynth_release_all(fm);
  fmsynth_free(fm);

  delete[] lBuffer;
  delete[] rBuffer;

  std::cout << "Shut down!" << std::endl;
  delete snd;
  return 0;
}
