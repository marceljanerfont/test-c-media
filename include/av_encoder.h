#ifndef __AV_ENCODER_H__        
#define __AV_ENCODER_H__        

#include <string>
#include <vector>

extern "C" {
#define __STDC_CONSTANT_MACROS
#include <libavformat/avformat.h>
#include <libavutil/avassert.h>
#include <libavutil/opt.h>
}

#include "../include/av_decoder.h"

class AVEncoder {
public:
    AVEncoder();
    ~AVEncoder();

    void                    Open(const AVCodecContext* pDecoderContext);
    bool                    IsInitiated() const;
    void                    Close();
    std::vector<AVPacket*>  Encode(AVFrame* frame);
    AVCodec*                GetAVCodec();
    AVCodecContext*         GetAVCodecContext();

private:
    void InitFromDecoder();

    uint64_t                m_packet_counter;
    std::string             m_codecName;
    AVCodec*                m_pCodec;
    AVCodecContext*         m_pCodecContext;
    const AVCodecContext*   m_pDecoderContext;
};


#endif // __AV_ENCODER_H__
