#ifndef __AV_READER_H__    
#define __AV_READER_H__    

#include <string>

extern "C" {
#define __STDC_CONSTANT_MACROS
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
#include <libavutil/avassert.h>
#include <libavutil/audio_fifo.h>
#include <libavutil/opt.h>
}

class AVReader {
public:
    AVReader();
    ~AVReader();

    void             Open(const std::string& filepath);
    void             Close();
    AVPacket*        Read();

private:
    std::string      m_filepath;
    AVFormatContext* m_pInputFormatContext;
};


#endif // __AV_READER_H__
