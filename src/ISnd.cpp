#include "ISnd.hpp"

#include <iostream>
#include <stdexcept>

#include "staticFnc.hpp"

ISnd::ISnd(unsigned int sampleRate){
  int err;
  snd_pcm_hw_params_t *hw_params;

  std::cout << "Open PCM." << std::endl;
  err = snd_pcm_open (&h_pb, "hw:0", SND_PCM_STREAM_PLAYBACK, 0);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));

  std::cout << "Get hardware parameters." << std::endl;
  err = snd_pcm_hw_params_malloc (&hw_params);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));

  err = snd_pcm_hw_params_any (h_pb, hw_params);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));

  std::cout << "Set hardware parameters access mode." << std::endl;
  err = snd_pcm_hw_params_set_access (h_pb, hw_params, SND_PCM_ACCESS_RW_NONINTERLEAVED);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));

  std::cout << "Set hardware parameters format." << std::endl;
  if(isBigEndian())
  {
    std::cout << "System is Big Endian." << std::endl;
    err = snd_pcm_hw_params_set_format (h_pb, hw_params, SND_PCM_FORMAT_FLOAT_BE);
  }
  else
  {
      std::cout << "System is Big Endian." << std::endl;
      err = snd_pcm_hw_params_set_format (h_pb, hw_params, SND_PCM_FORMAT_FLOAT_LE);
  }
  if ( err < 0) throw std::runtime_error(snd_strerror(err));

  std::cout << "Set sample rate." << std::endl;
  err = snd_pcm_hw_params_set_rate_near (h_pb, hw_params, &sampleRate, 0);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));

  std::cout << "Set Chanel Count" << std::endl;
  err = snd_pcm_hw_params_set_channels (h_pb, hw_params, 2);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));

  std::cout << "Set Hardware Parameters" << std::endl;
  err = snd_pcm_hw_params (h_pb, hw_params);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));

  snd_pcm_hw_params_free (hw_params);

  std::cout << "Prepare Sound device" << std::endl;
  err = snd_pcm_prepare (h_pb);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));

  bufs = new void*[2];
}

void ISnd::PlayBuffers(float* lBuffer, float* rBuffer, size_t frameCount){
  int err;

  std::cout << "Play Buffer" << std::endl;

  bufs[0] = lBuffer;
  bufs[1] = rBuffer;

  err = snd_pcm_writen (h_pb, bufs, frameCount);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));

}

ISnd::~ISnd(){
  snd_pcm_close (h_pb);
}
