#include "Rndr.hpp"

Rndr::Rndr(ISnd &snd) : m_snd(snd), m_Drctr(Drctr(snd.getSampleRate()))
{

}

void Rndr::Run()
{
  float* buf = new float[m_snd.getFrameCount()];

  while(m_running)
  {
    std::fill(buf, buf + m_snd.getFrameCount(), 0);

    m_Drctr.AddLayer(buf, m_snd.getFrameCount());

    m_snd.PlayBuffers(buf);
  }

  delete[] buf;
}

void Rndr::Stop()
{
  m_running = false;
}

bool Rndr::IsRunning()
{
  return m_running;
}
