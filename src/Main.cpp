#include <fmsynth.h>
#include <iostream>

int main() {
  //std::cout << "Start up!" << std::endl;

  float* lBuffer = new float[8096];
  float* rBuffer = new float[8096];

  fmsynth_t* fm = fmsynth_new(44100, 1);
  fmsynth_note_on(fm, 80, 20);

  fmsynth_render(fm, lBuffer, rBuffer, 8096);

  for(int i = 0; i < 8096; i++)
  {
    std::cout << static_cast<char>(lBuffer[i] * 256);
  }

  fmsynth_release_all(fm);
  fmsynth_free(fm);

  //std::cout << "Shut down!" << std::endl;
  return 0;
}
