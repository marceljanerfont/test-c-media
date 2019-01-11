//#include <chrono> 
#include <vector>

#include "src/utils/ffmpeg_utils.h"

namespace ffmpeg {
    char *const get_error_text(const int error) {
        static char error_buffer[512];
        av_strerror(error, error_buffer, sizeof(error_buffer));
        if (error == AVERROR(EAGAIN)) {
            strcat_s(error_buffer, "- [av_read_frame TIMEOUT] -");
        }
        return error_buffer;
    }

    void free_packets(std::vector<AVPacket*>& packets) {
        for (AVPacket* packet : packets) {
            av_packet_unref(packet);
        }
        packets.clear();
    }

    void free_frames(std::vector<AVFrame*>& frames) {
        for (AVFrame* frame : frames) {
            av_frame_unref(frame);
        }
        frames.clear();
    }

} // namespace ffmpeg
