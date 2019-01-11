
## FFMPEG 4.0
#set(FFMPEGDIR "ffmpeg-7395f13-lgpl")
set(FFMPEGDIR "ffmpeg-4.0-win64-dev")
set (MSVC12RUNTIME "microsoftVC_redist-12.0")
include_directories("${APIS_PATH}/${FFMPEGDIR}/include")
link_directories("${APIS_PATH}/${FFMPEGDIR}/lib")
set(LIBS_FFMPEG  avcodec
                  avformat
                  avdevice
                  avfilter
                  swresample
                  swscale
                  avutil)
                  
SET(FFMPEG_DEPENDENCIES 
	"${APIS_PATH}/${FFMPEGDIR}/bin/avcodec-58.dll"
	"${APIS_PATH}/${FFMPEGDIR}/bin/avdevice-58.dll"
	"${APIS_PATH}/${FFMPEGDIR}/bin/avfilter-7.dll"
	"${APIS_PATH}/${FFMPEGDIR}/bin/avformat-58.dll"
	"${APIS_PATH}/${FFMPEGDIR}/bin/avutil-56.dll"
	"${APIS_PATH}/${FFMPEGDIR}/bin/swresample-3.dll"
	"${APIS_PATH}/${FFMPEGDIR}/bin/swscale-5.dll" 
	"${APIS_PATH}/${FFMPEGDIR}/bin/ffmpeg.exe" 
	"${APIS_PATH}/${FFMPEGDIR}/bin/ffplay.exe" 
	"${APIS_PATH}/${FFMPEGDIR}/bin/ffprobe.exe"
  )