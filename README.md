# AV Multimedia (C/C++) Test


The main goal is to make live streaming of a video sourced from an audio and video file previously recorded.

The intention of this exercise is to demonstrate the ability to process audio video, C++ coding and multithreading.

## Scenerio
```
audio file (audio.aac) -> DEC -> ENC \
                                      -> WRITE -> live stream (mpegts) 
video file (video.h264)-> DEC -> ENC /
```

* INPUTS: 
    * audio source file is located in `media/audio.aac` encoded by AAC
    * video source file in `media/video.h264` encoded by H.264
* DEC: decoder
* ENC: encoder
* WRITE: multiplexer of encoded audio and encoded video  and  output writer (live stream) 
* OUPUT: live stream

### Given Tools (Optional)
It is provided a small framework stacked over FFMPEG 4.0 (you can use it or not, it's your choice). It has been used under Visual Studio 2017.
The ffmpeg 4.0 win64 can be download from:

* lib: [https://ffmpeg.zeranoe.com/builds/win64/dev/ffmpeg-4.0-win64-dev.zip](https://ffmpeg.zeranoe.com/builds/win64/dev/ffmpeg-4.0-win64-dev.zip)
* bin: [https://ffmpeg.zeranoe.com/builds/win64/dev/ffmpeg-4.0-win64-dev.zip](https://ffmpeg.zeranoe.com/builds/win64/dev/ffmpeg-4.0-win64-dev.zip)

The small framework is composed of:

* AVRead: reads compressed audio and video AVPackets from sources 
* AVDecoder: decodes AAC or H264 AVPackets to AVFrames
* AVEncoder: encodes uncompressed audio and video AVFrames to AAC or H264 AVPackets
* AVWriter(TODO): writes compressed audio and video AVPackets into live stream output.

*IT IS YOUR CHOICE USE IT OR NOT*

## Goals
### Stage 1: *LIVE STREAMING* (Mandatory)
The audio and video sources must be DECODED and ENCODED in AAC and H264 again and MULTIPLEXED into live streaming.

The live streaming should be in MPEG TS format and streamed on a network protocol like TCP or UDP. Localhost works. Live streamed should be played by `ffplay.exe` (ffmpeg) at real time.

### Stage 2: *AV FILTER* (Optional)
Implement audio or video filter of your choice. For instance, a video filter could be a black & white filter. And the audio filter could be used to tone a signal or implement an echo filter.

Whatever that modifies the audio and/or the video.



