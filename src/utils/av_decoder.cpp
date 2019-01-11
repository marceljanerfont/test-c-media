#include <iostream>
#include <sstream>

#include "src/utils/av_decoder.h"
#include "src/utils/ffmpeg_utils.h"


AVDecoder::AVDecoder(): m_pCodec(nullptr)
, m_pCodecContext(nullptr) {
//, m_pParser(nullptr) {
}

AVDecoder::~AVDecoder() {
    Close();
}

void AVDecoder::Open(AVCodecID codecID) {
    int error = 0;
    m_pCodec = avcodec_find_decoder(codecID);
    if (!m_pCodec) {
        throw std::exception("Codec not found");
    }
    m_codecName = std::string(m_pCodec->name);

    //m_pParser = av_parser_init(m_pCodec->id);
    //if (!m_pParser) {
    //    throw std::exception("Parser not found");
    //}

    m_pCodecContext = avcodec_alloc_context3(m_pCodec);
    if (!m_pCodecContext) {
        throw std::exception("Could not allocate video decoder context");
    }

    if ((error = avcodec_open2(m_pCodecContext, m_pCodec, nullptr)) < 0) {
        throw std::exception("Could not open codec");
    }
}

void AVDecoder::Close() {
    //if (m_pParser) {
    //    av_parser_close(m_pParser);
    //    m_pParser = nullptr;
    //}
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
std::vector<AVFrame*> AVDecoder::Decode(AVPacket* packet) {
    int error = 0;
    std::vector<AVFrame*> frames;

    // send the packet with the compressed data to the decoder
    if ((error = avcodec_send_packet(m_pCodecContext, packet)) < 0) {
        std::ostringstream oss;
        oss << m_codecName << " has failed submitting the packet to the decoder. Error: " << ffmpeg::get_error_text(error);
        throw std::exception(oss.str().c_str());
    }

    // one packet may be decoded into many frames
    while (error >= 0) {
        AVFrame* frame = av_frame_alloc(); // av_frame_unref
        if ((error = avcodec_receive_frame(m_pCodecContext, frame)) < 0) {
            av_frame_unref(frame);
            if (error == AVERROR_EOF || error == AVERROR(EAGAIN)) {
                // no more to decode
                break;
            } else { 
                // error
                std::ostringstream oss;
                oss << m_codecName << " has failed during decoding. Error: " << ffmpeg::get_error_text(error);
                throw std::exception(oss.str().c_str());
            }
        } else {
            // no error: error >= 0
            frames.push_back(frame);
            if (m_pCodecContext->frame_number % 10 == 0) {
                std::cout << m_codecName << " decoded frame " << m_pCodecContext->frame_number << std::endl;
            }
        }
    }
    return frames;
}

AVCodecContext* AVDecoder::GetAVCodecContext() {
    return m_pCodecContext;
}

AVCodec* AVDecoder::GetAVCodec() {
    return m_pCodec;
}
