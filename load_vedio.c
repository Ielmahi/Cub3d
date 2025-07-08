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
    AVPacket *pack;
    AVFrame *frame = av_frame_alloc(), *rgb_frame = av_frame_alloc();
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
      w = SDL_CreateWindow(
                  "Hi",
                   SDL_WINDOWPOS_CENTERED,
                   SDL_WINDOWPOS_CENTERED,
                    1600,
                    1200,
                    SDL_WINDOW_SHOWN);
      pack = av_packet_alloc();
    if(!pack) return 1;
    while(!(av_read_frame(info_file, pack) < 0))
  {
    if(pack->stream_index == vedio_stream_index)
    {
           avcodec_send_packet(dec_ctx, packet);
            while(!avcodec_receive_frame(packet, frame))
            {
                  sws_scale(dec_ctx,
                frame->data, frame->linesize,
                0, frame->height,
                    rgb_frame->data, rgb_frame->linesize);
            }
    }
  }
}
