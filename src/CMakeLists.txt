file(GLOB SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
message("Main sources: ${SRCS}")

include(../cmake/libs/ffmpeg.cmake)

add_executable(main ${SRCS})
target_link_libraries(main
    ${LIBS_FFMPEG})