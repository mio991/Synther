#pragma once

#include "ISnd.hpp"
#include "Drctr.hpp"

#include <iostream>

class Rndr
{
public:
  Rndr(ISnd &snd);
  void Run();
  void Stop();
  bool IsRunning();
private:
  ISnd &m_snd;
  bool m_running = true;
  Drctr m_Drctr;
};
