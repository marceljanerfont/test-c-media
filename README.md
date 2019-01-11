# AV Multimedia (C/C++) Test


The main goal is to make live streaming of a video sourced from an audio and video file previously recorded.
The purpose of this exercise is to demonstrate the ability to process audio video, C++ coding and multithreading.

### Prerequisites

* CMake (3.12 or newer) available from [https://cmake.org]
* Visual Studio 2015 (2017 recommended) (Community Edition is availalbe at [https://visualstudio.microsoft.com]
* FFMpeg 4.1 libraries : [https://ffmpeg.zeranoe.com] 
    * headers & libs: [https://ffmpeg.zeranoe.com/builds/win64/dev/ffmpeg-4.1-win64-dev.zip] 
    * binaries: [https://ffmpeg.zeranoe.com/builds/win64/shared/ffmpeg-4.1-win64-shared.zip] 
* Windows 7 x64 or newer (Windows 10 x64 recommended)

### Initial setup

1. create a "devel" folder in your hard disk (f.i C:\devel)
2. unzip ffmpeg 4.1 libraries. This will create two separate ffmpeg-4.1-win64-dev and ffmpeg-4.1-win64-shared folders.
3. Copy the contents of both folders into a devel/ffmpeg-4.1 folder
4. create an user enviroment variable (APIS_PATH) pointing to your devel folder (for instance APIS_PATH=C:\devel)
5. Generate the project using the Visual studio 2017 (Win64) generator either via the gui tool or from the command line:
```bash
cmake -G "Visual Studio 15 2017 Win64"   <PATH_TO_CLONED_REPOSITORY>
```

### Workflow
```
audio file (audio.aac) -> DEC (Stereo PCM) -> ENC (AAC-LC)\
                                      -> WRITE -> live stream (mpegts) 
video file (video.h264)-> DEC (RGB24)-> ENC  (H.264)/
```

* INPUTS: 
    * audio source file is located in `media/audio.aac` encoded by AAC
    * video source file in `media/video.h264` encoded by H.264
* DEC: decoder
* ENC: encoder
* WRITE: multiplexer of encoded audio and encoded video  and  output writer (live stream) 
* OUPUT: live stream

### Given Tools (Optional)
We have provided a small set of classes for reading, encoding and decoding A/V streams via FFMPEG 4.1.
This basic framework includes the following tools:

* AVRead: reads compressed audio and video AVPackets from sources 
* AVDecoder: decodes AAC or H264 AVPackets to AVFrames
* AVEncoder: encodes uncompressed audio and video AVFrames to AAC or H264 AVPackets
* AVWriter (write should be implemented by the user): writes compressed audio and video AVPackets into live stream output.

*Note: Using these utilities is entirely optional. IT IS YOUR CHOICE USE IT OR NOT*

## Goals
### Stage 1: *LIVE STREAMING* (Mandatory)
The audio and video sources must be firstly DECODED into separate raw video (RGB)  and audio (PCM stereo) frames. Next, Each RGB frame will be sent to a H264  ENCODER (CPU or GPU implementation), which will provide codec video packets . Likewise, the decoded PCM samples will be sent to a AAC-LC encoder to generate audio packets. Each time a new set of video and audio sample is ready, they should be sent to your muxer implementation, which will output it to a network destination.

The live streaming must use  a MPEG transport stream (TS) container and streamed on a network protocol such as TCP or UDP, either via Ipv6 or ipv4. Localhost works ([::1] or 127.0.0.1). Ensure that the livestream is  playailable via  the `ffplay.exe` bundled with ffmpeg 4.1  or other similar tools such as Videolan (VLC).

### Stage 2: *AV FILTER* (Optional)
Implement audio or video filter of your choice. For instance, a video filter could be a black & white filter. And the audio filter could be used to tone a signal or implement an echo filter.

Whatever that modifies the audio and/or the video.

#### additional notes
ffmpeg provides several examples for various A/V worfklows in the "examples" folder)
have f

