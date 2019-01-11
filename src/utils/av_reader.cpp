#include <sstream>

#include "src/utils/av_reader.h"
#include "src/utils/ffmpeg_utils.h"


AVReader::AVReader(): m_pInputFormatContext(nullptr) {
}

AVReader::~AVReader() {
    Close();
}

void AVReader::Open(const std::string& filepath) {
    m_filepath = filepath;
    m_pInputFormatContext = avformat_alloc_context();
    int error;
    // open
    if ((error = avformat_open_input(&m_pInputFormatContext, m_filepath.c_str(), nullptr, nullptr)) < 0) {
        std::ostringstream oss;
        oss << "Could not open input file " << m_filepath << ". Error: " << ffmpeg::get_error_text(error);
        throw std::exception(oss.str().c_str());
    }
    // find stream info
    if ((error = avformat_find_stream_info(m_pInputFormatContext, nullptr)) < 0) {
        std::ostringstream oss;
        oss << "Could not open find stream info. Error: " << ffmpeg::get_error_text(error);
        throw std::exception(oss.str().c_str());
    }
    if (m_pInputFormatContext->nb_streams < 1) {
        std::ostringstream oss;
        throw std::exception("There is not any audior or video stream");
    }
}

void AVReader::Close() {
    if (m_pInputFormatContext) {
        avformat_close_input(&m_pInputFormatContext);
        m_pInputFormatContext = nullptr;
    }
}

AVPacket* AVReader::Read() {
    AVPacket* packet = av_packet_alloc();
    av_init_packet(packet); // then call: av_packet_unref(&packet);
    packet->data = nullptr;
    packet->size = 0;
    int error;
    if ((error = av_read_frame(m_pInputFormatContext, packet)) < 0) {
        if (error != AVERROR_EOF) {
            std::ostringstream oss;
            oss << "Error reading  " << m_filepath << ". Error: " << ffmpeg::get_error_text(error);
            av_packet_unref(packet);
            throw std::exception(oss.str().c_str());
        }
        av_packet_unref(packet);
        return nullptr;
    }
    return packet;
}
