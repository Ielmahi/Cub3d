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
    //========================================================================== 
    AVFormatContext *info_file; 
    AVCodec *codec; 
    SDL_Window *w; 
    AVPacket *pack; 
    SDL_Renderer *render;   // fix: pointer not struct 
    AVFrame *frame = av_frame_alloc(), *rgb_frame = av_frame_alloc(); 
    int num_bytes; 
 
    // Missing variable dec_ctx declared here (was used before) 
    AVCodecContext *dec_ctx; 
 
    //========================================================================= 
    info_file = NULL; 
    if (avformat_open_input(&info_file, PATH, NULL, NULL) < 0) 
        return (1); 
    if (avformat_find_stream_info(info_file, NULL) < 0) 
        return (1); 
 
    // Find video stream index (was missing, you used vedio_stream_index later) 
    int vedio_stream_index = -1; 
    for (unsigned int i = 0; i < info_file->nb_streams; i++) { 
        if (info_file->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) { 
            vedio_stream_index = i; 
            break; 
        } 
    } 
    if (vedio_stream_index == -1) 
        return 1; 
 
    codec = avcodec_find_decoder(info_file->streams[vedio_stream_index]->codecpar->codec_id); 
    if (!codec) 
        return (1); 
 
    dec_ctx = avcodec_alloc_context3(codec); 
    avcodec_parameters_to_context(dec_ctx, info_file->streams[vedio_stream_index]->codecpar); 
    if (avcodec_open2(dec_ctx, codec, NULL) < 0) 
        return (1); 
 
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
        return 1; 
 
    w = SDL_CreateWindow( 
        "Hi", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        dec_ctx->width, 
        dec_ctx->height, 
        SDL_WINDOW_SHOWN); 
 
    render = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED); // fixed typo 
 
    // RGB-> R 1 G 1 B 1 ---> 3bytes 
    SDL_Texture *texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, dec_ctx->width, dec_ctx->height); // fixed typo 
 
    num_bytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24, dec_ctx->width, dec_ctx->height, 1); 
    uint8_t *buffer = av_malloc(num_bytes); 
 
    av_image_fill_arrays( 
        rgb_frame->data, 
        rgb_frame->linesize, 
        buffer, 
        AV_PIX_FMT_RGB24, 
        dec_ctx->width, 
        dec_ctx->height, 
        1); 
 
    struct SwsContext *sws_ctx = sws_getContext( 
        dec_ctx->width, 
        dec_ctx->height, 
        dec_ctx->pix_fmt, 
        dec_ctx->width, 
        dec_ctx->height, 
        AV_PIX_FMT_RGB24, 
        SWS_BILINEAR, 
        NULL, 
        NULL, 
        NULL); 
 
    if (!render) 
        return 1; 
 
    pack = av_packet_alloc(); 
    if (!pack) 
        return 1; 
 
    while (av_read_frame(info_file, pack) >= 0) 
    { 
        if (pack->stream_index == vedio_stream_index) 
        { 
            avcodec_send_packet(dec_ctx, pack); 
            while (avcodec_receive_frame(dec_ctx, frame) == 0) // fixed wrong arguments 
            { 
                sws_scale( 
                    sws_ctx, 
                    frame->data, 
                    frame->linesize, 
                    0, 
                    frame->height, 
                    rgb_frame->data, 
                    rgb_frame->linesize); 
 
                SDL_UpdateTexture(texture, NULL, rgb_frame->data[0], rgb_frame->linesize[0]); 
                SDL_RenderClear(render); 
                SDL_RenderCopy(render, texture, NULL, NULL); 
                SDL_RenderPresent(render); 
                //SDL_Delay(); 
            } 
        } 
        av_packet_unref(pack); 
    } 
 
    SDL_Quit(); 
 
    return 0; 
} 
