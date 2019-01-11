#ifndef __AV_DECODER_H__        
#define __AV_DECODER_H__        

#include <string>
#include <vector>

extern "C" {
#define __STDC_CONSTANT_MACROS
#include <libavformat/avformat.h>
#include <libavutil/avassert.h>
#include <libavutil/opt.h>
}

class AVDecoder {
public:
    AVDecoder();
    ~AVDecoder();

    void                    Open(AVCodecID codecID);
    void                    Close();
    std::vector<AVFrame*>   Decode(AVPacket* packet);
    AVCodec*                GetAVCodec(); 
    AVCodecContext*         GetAVCodecContext();


private:
    std::string             m_codecName;
    AVCodec*                m_pCodec;
    AVCodecContext*         m_pCodecContext;
    //AVCodecParserContext*   m_pParser;
};


#endif // __AV_DECODER_H__
