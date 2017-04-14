#include <fmsynth.h>
#include <iostream>
#include <algorithm>
#include <thread>

#include <cstdlib>

#include "ISnd.hpp"
#include "Rndr.hpp"

static unsigned int SAMPLE_RATE = 44100;

int main(int argc, char const *argv[])
{
  float volMultiplier = 1;

  if(argc > 1)
  {
    volMultiplier = atof(argv[1]);
  }

  std::cout << "Start up!" << std::endl;

  ISnd snd = ISnd(SAMPLE_RATE, volMultiplier);

  std::cout << "Frame Count: " << snd.getFrameCount() << std::endl;

  Rndr rndr = Rndr(snd);

  std::thread trndr([](Rndr &rndr){rndr.Run();}, std::ref(rndr));

  std::cout << "Press a key to end playback...";
  char p;
  std::cin >> p;

  std::cout << "Stop Renderer" << std::endl;
  rndr.Stop();

  trndr.join();

  std::cout << "Shut down!" << std::endl;
  return 0;
}
