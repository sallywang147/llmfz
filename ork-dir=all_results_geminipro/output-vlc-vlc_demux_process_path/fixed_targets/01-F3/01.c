#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <libavutil/avutil.h>
#include <libavformat/avformat.h>

extern "C" {
#include <libvlc/libvlc.h>
}

int LLVMFuzzerInitialize(int *argc, char ***argv) {
  (void)argc;
  (void)argv;

  libvlc_instance_t *vlc = libvlc_new(0, NULL);
  if (!vlc) {
    return -1;
  }

  return 0;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *path = str.c_str();

  libvlc_media_t *media = libvlc_media_new_path(vlc, path);
  if (!media) {
    return -1;
  }

  libvlc_media_player_t *player = libvlc_media_player_new(vlc);
  if (!player) {
    libvlc_media_release(media);
    return -1;
  }

  libvlc_media_player_set_media(player, media);
  libvlc_media_release(media);

  libvlc_media_player_play(player);

  while (libvlc_media_player_is_playing(player)) {
    // Wait for the player to finish playing.
  }

  libvlc_media_player_release(player);

  return 0;
}