#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "vlc/vlc.h"

extern "C" {
#include "vlc/libvlc_internal.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  libvlc_instance_t *libvlc_instance = libvlc_new(0, NULL);
  libvlc_media_t *media = libvlc_media_new_memory(libvlc_instance, data, size);
  libvlc_media_player_t *media_player = libvlc_media_player_new_from_media(media);
  libvlc_media_release(media);

  libvlc_media_player_play(media_player);
  while (libvlc_media_player_is_playing(media_player)) {
    // Do something while the media is playing
  }

  libvlc_media_player_stop(media_player);
  libvlc_media_player_release(media_player);
  libvlc_release(libvlc_instance);

  return 0;
}