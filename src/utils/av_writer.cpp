#include <sstream>

#include "src/utils/av_writer.h"
#include "src/utils/ffmpeg_utils.h"


AVWriter::AVWriter(): m_pOutputFormatContext(nullptr)
, m_pAudioStream(nullptr) 
, m_pVideoStream(nullptr) {
}

AVWriter::~AVWriter() {
    Close();
}

void AVWriter::Open(const std::string& url, AVCodecContext* pAudioCodecContext, AVCodecContext* pVideoCodecContext) {
    int error;
    m_url = url;
    m_pAudioCodecContext = pAudioCodecContext;
    m_pVideoCodecContext = pVideoCodecContext;
    // allocate the output media context
    avformat_alloc_output_context2(&m_pOutputFormatContext, NULL, "mpegts", m_url.c_str());
    if (!m_pOutputFormatContext) {
        throw std::exception("Could not deduce output format from file extension:");
    }
    // add audio stream
    AddStream(&m_pAudioStream, m_pAudioCodecContext);

    // add video stream
    AddStream(&m_pVideoStream, m_pVideoCodecContext);

    // open
    if ((error = avio_open2(&m_pOutputFormatContext->pb, m_url.c_str(), AVIO_FLAG_READ_WRITE, NULL, NULL)) < 0) {
        throw std::exception("Could not deduce output format from file extension:");
    }
}

void AVWriter::Close() {
    if (m_pOutputFormatContext) {
        avio_close(m_pOutputFormatContext->pb);
        avformat_free_context(m_pOutputFormatContext);
        m_pOutputFormatContext = nullptr;
    }
}

// TODO: 
void AVWriter::WriteAudio(AVPacket* packet) {
    //packet->stream_index = m_pAudioStream->index;
    //int ret = av_interleaved_write_frame(m_pOutputFormatContext, packet);
    //avio_flush(m_pOutputFormatContext->pb);
}

// TODO: 
void AVWriter::WriteVideo(AVPacket* packet) {
    //packet->stream_index = m_pVideoStream->index;
    //int ret = av_interleaved_write_frame(m_pOutputFormatContext, packet);
    //avio_flush(m_pOutputFormatContext->pb);
}

// TODO: 
void AVWriter::AddStream(AVStream** stream, AVCodecContext* codecContext) {
    //int error;

    //*stream = avformat_new_stream(m_pOutputFormatContext, codecContext->codec);

    //if (!(stream->codec = avcodec_alloc_context3(codecContext->codec))) {
    //    throw std::exception("Could not allocate stream codec");
    //}

    //if ((error = avcodec_parameters_from_context(stream->codecpar, codecContext)) < 0) {
    //    throw std::exception("Could not copy the stream parameters");
    //}
}

bool AVWriter::IsInitiated() const {
    return m_pOutputFormatContext && m_pAudioStream && m_pVideoStream;
}
