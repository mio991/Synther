#include "ISnd.hpp"

#include <iostream>
#include <stdexcept>

#define ALSAExec(txt, cmd) std::cout << txt << std::endl;\
  err = cmd;\
  if ( err < 0) throw std::runtime_error(snd_strerror(err));


ISnd::ISnd(unsigned int sampleRate){
  int err;
  snd_pcm_hw_params_t *hw_params;

  ALSAExec("Open PCM.", snd_pcm_open (&h_pb, "default", SND_PCM_STREAM_PLAYBACK, 0))

/*
  std::cout << "Open PCM." << std::endl;
  err = snd_pcm_open (&h_pb, "default", SND_PCM_STREAM_PLAYBACK, 0);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));
*/
  std::cout << "Get hardware parameters." << std::endl;
  err = snd_pcm_hw_params_malloc (&hw_params);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));

  err = snd_pcm_hw_params_any (h_pb, hw_params);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));

  snd_pcm_access_mask_t * accessMask;
  snd_pcm_access_mask_malloc(&accessMask);

  snd_pcm_access_mask_set(accessMask, SND_PCM_ACCESS_RW_INTERLEAVED);
  snd_pcm_access_mask_set(accessMask, SND_PCM_ACCESS_RW_NONINTERLEAVED);

  std::cout << "Set hardware parameters access mode." << std::endl;
  err = snd_pcm_hw_params_set_access_mask (h_pb, hw_params, accessMask );
  if ( err < 0) throw std::runtime_error(snd_strerror(err));

  snd_pcm_access_mask_free(accessMask);

  std::cout << "Set hardware parameters format." << std::endl;
  err = snd_pcm_hw_params_set_format (h_pb, hw_params, SND_PCM_FORMAT_FLOAT);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));

  std::cout << "Set sample rate." << std::endl;
  err = snd_pcm_hw_params_set_rate_near (h_pb, hw_params, &sampleRate, 0);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));

  std::cout << "Set Chanel Count" << std::endl;
  err = snd_pcm_hw_params_set_channels (h_pb, hw_params, 1);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));

  std::cout << "Set Hardware Parameters" << std::endl;
  err = snd_pcm_hw_params (h_pb, hw_params);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));

  std::cout << "Get Frame count" << std::endl;
  err = snd_pcm_hw_params_get_period_size (hw_params, &frameCount, NULL);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));

  snd_pcm_hw_params_free (hw_params);

  std::cout << "Prepare Sound device" << std::endl;
  err = snd_pcm_prepare (h_pb);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));

  std::cout << "Get State" << std::endl;
  snd_pcm_state_t state = snd_pcm_state(h_pb);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));

  std::cout << "State: " << state << std::endl;

  bufs = new void*[2];
}

void ISnd::Start(){
  int err;

  std::cout << "Start Playback?" << std::endl;
  err = snd_pcm_start (h_pb);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));
}

void ISnd::PlayBuffers(float* lBuffer, float* rBuffer){
  int err;

/*
  bufs[0] = lBuffer;
  bufs[1] = rBuffer;

  err = snd_pcm_writen (h_pb, bufs, frameCount);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));
  std::cout << "Frames played: " << err << std::endl;
*/

  std::cout << "Interleave" << std::endl;
  float* buf = new float[frameCount*2];
  interleave(lBuffer, rBuffer, buf);


  std::cout << "Wait!" << std::endl;
  err = snd_pcm_wait(h_pb, -1);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));

  std::cout << "Play Buffer" << std::endl;
  err = snd_pcm_writei(h_pb, lBuffer, frameCount);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));
  std::cout << "Frames played: " << err << std::endl;

  delete[] buf;

}

void ISnd::interleave(float* l, float* r, float* res)
{
  for(int i = 0; i < frameCount; i++)
  {
    *res = *l ;
    res++;
    l++;

    *res = *r;
    res++;
    r++;
  }
}

size_t ISnd::getFrameCount(){
  return frameCount;
}

ISnd::~ISnd(){
  int err;

  std::cout << "Drain Device" << std::endl;
  err = snd_pcm_drain (h_pb);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));

  std::cout << "Close Device" << std::endl;
  err = snd_pcm_close (h_pb);
  if ( err < 0) throw std::runtime_error(snd_strerror(err));
}
