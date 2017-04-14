#include "Rndr.hpp";

Rndr::Rndr(ISnd &snd) : m_snd(snd){}
Rndr::~Rndr(){}

void Rndr::Run()
{
  float* lBuffer = new float[m_snd.getFrameCount()];
  float* rBuffer = new float[m_snd.getFrameCount()];

  fmsynth_t* fm = fmsynth_new(m_snd.getFrameCount(), 1);
  fmsynth_note_on(fm, 50, 24);

  while(m_running)
  {
    std::fill(lBuffer, lBuffer + m_snd.getFrameCount(), 0);
    std::fill(rBuffer, rBuffer + m_snd.getFrameCount(), 0);

    fmsynth_render(fm, lBuffer, rBuffer, m_snd.getFrameCount());
    m_snd.PlayBuffers(lBuffer, rBuffer);
  }

  fmsynth_free(fm);

  delete[] lBuffer;
  delete[] rBuffer;
}

void Rndr::Stop()
{
  m_running = false;
}

bool Rndr::IsRunning()
{
  return m_running;
}
