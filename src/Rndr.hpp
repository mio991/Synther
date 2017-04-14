#include "ISnd.hpp"

#include <fmsynth.h>
#include <iostream>

class Rndr
{
public:
  Rndr(ISnd &snd);
  ~Rndr();
  void Run();
  void Stop();
  bool IsRunning();
private:
  ISnd &m_snd;
  bool m_running = true;
};
