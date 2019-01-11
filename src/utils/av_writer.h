#ifndef __AV_WRITER_H__    
#define __AV_WRITER_H__    

#include <string>

extern "C" {
#define __STDC_CONSTANT_MACROS
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
#include <libavutil/avassert.h>
#include <libavutil/opt.h>
}

class AVWriter {
public:
    AVWriter();
    ~AVWriter();

    void             Open(const std::string& url, AVCodecContext* pAudioCodecContext, AVCodecContext* pVideoCodecContext);
    bool             IsInitiated() const;
    void             Close();
    void             WriteAudio(AVPacket* packet);
    void             WriteVideo(AVPacket* packet);

private:

    void            AddStream(AVStream** stream, AVCodecContext* codecContext);

    std::string      m_url;
    AVFormatContext* m_pOutputFormatContext;

    AVCodecContext*  m_pAudioCodecContext;
    AVCodecContext*  m_pVideoCodecContext;

    AVStream*       m_pAudioStream;
    AVStream*       m_pVideoStream;
};


#endif // __AV_WRITER_H__
