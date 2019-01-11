file(GLOB_RECURSE SRCS *.cpp *.h *.rc )
message("Main sources: ${SRCS}")
add_definitions( -DUNICODE -D_UNICODE )


add_executable(muxer ${SRCS})
target_link_libraries(muxer ${LIBS_FFMPEG})