#include <unistd.h>
#include <stdio.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libavutil/samplefmt.h>
#include <libavutil/timestamp.h>
#include <libswscale/swscale.h>
#include <SDL2/SDL.h>

#define PATH "/root/Cub3d/test_vedio/test.mp4"
int main()
{
    AVFormatContext *info_file;
    AVCodec *codec;
    SDL_Window *w;

    info_file = NULL;
    if (avformat_open_input(&info_file, PATH, NULL, NULL) < 0)
        return (1);
    if (avformat_find_stream_info(info_file, NULL) < 0)
        return (1);
    codec = avcodec_find_decoder(info_file->streams[0]->codecpar->codec_id);
    if (!codec)
        return (1);
    AVCodecContext *dec_ctx = avcodec_alloc_context3(codec);
     avcodec_parameters_to_context(dec_ctx, info_file->streams[0]->codecpar);
  if(avcodec_open2(dec_ctx, codec, NULL) < 0) return(1);
  if(SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
  while(1)
      w = SDL_CreateWindow(
                  "Hi",
                   SDL_WINDOWPOS_CENTERED,
                   SDL_WINDOWPOS_CENTERED,
                    1600,
                    1200,
                    SDL_WINDOW_SHOWN
                  );
}
