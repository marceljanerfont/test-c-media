#include <iostream>
#include <sstream>


#include "src/utils/av_encoder.h"
#include "src/utils/ffmpeg_utils.h"

/* check that a given sample format is supported by the encoder */
static int check_sample_fmt(const AVCodec *codec, enum AVSampleFormat sample_fmt)
{
    const enum AVSampleFormat *p = codec->sample_fmts;

    while (*p != AV_SAMPLE_FMT_NONE) {
        if (*p == sample_fmt)
            return 1;
        p++;
    }
    return 0;
}

/* just pick the highest supported samplerate */
static int select_sample_rate(const AVCodec *codec)
{
    const int *p;
    int best_samplerate = 0;

    if (!codec->supported_samplerates)
        return 44100;

    p = codec->supported_samplerates;
    while (*p) {
        if (!best_samplerate || abs(44100 - *p) < abs(44100 - best_samplerate))
            best_samplerate = *p;
        p++;
    }
    return best_samplerate;
}

/* select layout with the highest channel count */
static int select_channel_layout(const AVCodec *codec)
{
    const uint64_t *p;
    uint64_t best_ch_layout = 0;
    int best_nb_channels = 0;

    if (!codec->channel_layouts)
        return AV_CH_LAYOUT_STEREO;

    p = codec->channel_layouts;
    while (*p) {
        int nb_channels = av_get_channel_layout_nb_channels(*p);

        if (nb_channels > best_nb_channels) {
            best_ch_layout = *p;
            best_nb_channels = nb_channels;
        }
        p++;
    }
    return (int)best_ch_layout;
}


AVEncoder::AVEncoder(): m_pCodec(nullptr)
, m_pCodecContext(nullptr) {
}

AVEncoder::~AVEncoder() {
    Close();
}

void AVEncoder::Open(const AVCodecContext* pDecoderContext) {
    m_pDecoderContext = pDecoderContext;
    m_packet_counter = 0;
}

void AVEncoder::InitFromDecoder() {
    int error;
    AVDictionary *opts = nullptr;

    m_pCodec = avcodec_find_encoder(m_pDecoderContext->codec_id);
    if (!m_pCodec) {
        throw std::exception("Codec not found");
    }

    m_pCodecContext = avcodec_alloc_context3(m_pCodec);
    if (!m_pCodecContext) {
        throw std::exception("Could not allocate video encoder context");
    }
    m_codecName = std::string(m_pCodec->name);

    if (m_pDecoderContext->codec_type == AVMEDIA_TYPE_VIDEO) {
        m_pCodecContext->bit_rate = m_pDecoderContext->bit_rate;
        m_pCodecContext->height = m_pDecoderContext->height;
        m_pCodecContext->width = m_pDecoderContext->width;
        m_pCodecContext->pix_fmt = m_pCodec->pix_fmts[0];
        m_pCodecContext->framerate = m_pDecoderContext->framerate;
        m_pCodecContext->time_base = av_inv_q(m_pCodecContext->framerate);
        m_pCodecContext->gop_size = m_pDecoderContext->gop_size;
        m_pCodecContext->max_b_frames = m_pDecoderContext->max_b_frames;

        av_dict_set(&opts, "profile", "high", 0);
        av_dict_set(&opts, "preset", "superfast", 0);
        av_dict_set(&opts, "tune", "zerolatency", 0);
    } else {
        m_pCodecContext->sample_fmt = m_pCodec->sample_fmts[0];
        m_pCodecContext->bit_rate = m_pDecoderContext->bit_rate;
        m_pCodecContext->sample_rate = select_sample_rate(m_pCodec);
        m_pCodecContext->channel_layout = select_channel_layout(m_pCodec);
        m_pCodecContext->channels = av_get_channel_layout_nb_channels(m_pCodecContext->channel_layout);
        m_pCodecContext->profile = FF_PROFILE_AAC_LOW;
    }

    // open it
    if ((error = avcodec_open2(m_pCodecContext, m_pCodec, &opts)) < 0) {
        std::ostringstream oss;
        oss << "Cannot open codec " << m_codecName << ". Error: " << ffmpeg::get_error_text(error);
        throw std::exception(oss.str().c_str());
    }
}

void AVEncoder::Close() {
    if (m_pCodecContext) {
        avcodec_free_context(&m_pCodecContext);
        m_pCodecContext = nullptr;
    }
    if (m_pCodec) {
        av_free(m_pCodec);
        m_pCodec = nullptr;
    }
}

// can return null
std::vector<AVPacket*> AVEncoder::Encode(AVFrame* frame) {
    int error = 0;
    std::vector<AVPacket*> packets;

    if (!m_pCodecContext) {
        InitFromDecoder();
    }

    // send the packet with the compressed data to the decoder
    if ((error = avcodec_send_frame(m_pCodecContext, frame)) < 0) {
        std::ostringstream oss;
        oss << m_codecName << " has failed submitting the frame to the m_pCodec. Error: " << ffmpeg::get_error_text(error);
        throw std::exception(oss.str().c_str());
    }

    while (error >= 0) {
        AVPacket* packet = av_packet_alloc();
        av_init_packet(packet); // then call: av_packet_unref(&packet);
        if ((error = avcodec_receive_packet(m_pCodecContext, packet)) < 0) {
            av_packet_unref(packet);
            if (error == AVERROR_EOF || error == AVERROR(EAGAIN)) {
                // no more to encode
                break;
            } else {
                // error
                std::ostringstream oss;
                oss << m_codecName << " has failed during encoding. Error: " << ffmpeg::get_error_text(error);
                throw std::exception(oss.str().c_str());
            }
        } else {
            // encoded ok
            packets.push_back(packet);
            ++m_packet_counter;
            if (m_packet_counter % 10 == 0) {
                std::cout << m_codecName << " encoded packet " << m_packet_counter << std::endl;
            }
        }
    }
    return packets;
}

AVCodecContext* AVEncoder::GetAVCodecContext() {
    return m_pCodecContext;
}

AVCodec* AVEncoder::GetAVCodec() {
    return m_pCodec;
}

bool AVEncoder::IsInitiated() const {
    return m_pCodecContext && m_pCodecContext->codec;
}
