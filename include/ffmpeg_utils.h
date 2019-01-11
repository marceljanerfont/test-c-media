#ifndef __FFMPEG_UTILS_H__
#define __FFMPEG_UTILS_H__

#include <vector>

extern "C" {
#define __STDC_CONSTANT_MACROS
#include <libavformat/avformat.h>
#include <libavutil/avassert.h>
#include <libavutil/opt.h>
}

namespace ffmpeg {
    char *const get_error_text(const int error);
    void free_packets(std::vector<AVPacket*>& packets);
    void free_frames(std::vector<AVFrame*>& frames);
} // namespace ffmpeg


#endif // __FFMPEG_UTILS_H__
