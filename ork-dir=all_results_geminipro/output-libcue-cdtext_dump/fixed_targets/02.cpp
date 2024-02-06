#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libavformat/avformat.h"

extern "C" {
#include "libavutil/avutil.h"
}

void cdtext_dump(struct Cdtext *cdtext, int verbose) {
  if (!cdtext)
    return;

  if (verbose)
    printf("Title: %s\n", cdtext->title);
  if (verbose)
    printf("Performer: %s\n", cdtext->performer);
  if (verbose)
    printf("Songwriter: %s\n", cdtext->songwriter);
  if (verbose)
    printf("Composer: %s\n", cdtext->composer);
  if (verbose)
    printf("Arranger: %s\n", cdtext->arranger);
  if (verbose)
    printf("Message: %s\n", cdtext->message);
  if (verbose)
    printf("Genre: %s\n", cdtext->genre);
  if (verbose)
    printf("Year: %s\n", cdtext->year);
  if (verbose)
    printf("UPC/EAN: %s\n", cdtext->upc_ean);
  if (verbose)
    printf("ISRC: %s\n", cdtext->isrc);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  AVFormatContext *fmt_ctx = NULL;
  AVIOContext *avio_ctx = NULL;
  uint8_t *avio_ctx_buffer = NULL;
  int ret = 0;

  avio_ctx_buffer = (uint8_t *)av_malloc(size);
  if (!avio_ctx_buffer) {
    ret = AVERROR(ENOMEM);
    goto end;
  }

  memcpy(avio_ctx_buffer, data, size);

  avio_ctx = avio_alloc_context(avio_ctx_buffer, size, 0, NULL, NULL, NULL, NULL);
  if (!avio_ctx) {
    ret = AVERROR(ENOMEM);
    goto end;
  }

  fmt_ctx = avformat_alloc_context();
  if (!fmt_ctx) {
    ret = AVERROR(ENOMEM);
    goto end;
  }

  fmt_ctx->pb = avio_ctx;

  ret = avformat_open_input(&fmt_ctx, NULL, NULL, NULL);
  if (ret < 0) {
    goto end;
  }

  ret = avformat_find_stream_info(fmt_ctx, NULL);
  if (ret < 0) {
    goto end;
  }

  for (unsigned int i = 0; i < fmt_ctx->nb_streams; i++) {
    AVStream *stream = fmt_ctx->streams[i];
    if (stream->codecpar->codec_type == AVMEDIA_TYPE_DATA) {
      AVPacket pkt;
      av_init_packet(&pkt);
      pkt.data = NULL;
      pkt.size = 0;

      while (av_read_frame(fmt_ctx, &pkt) >= 0) {
        if (pkt.stream_index == i) {
          struct Cdtext *cdtext = NULL;
          cdtext = av_cdtext_parse(pkt.data, pkt.size);
          if (cdtext) {
            cdtext_dump(cdtext, 1);
            av_cdtext_free(cdtext);
          }
        }
        av_packet_unref(&pkt);
      }
    }
  }

end:
  avformat_close_input(&fmt_ctx);
  av_free(avio_ctx_buffer);
  av_free(avio_ctx);
  return 0;
}