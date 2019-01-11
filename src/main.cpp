#include <iostream>
#include <thread>
#include <chrono>

#include "../include/ffmpeg_utils.h"
#include "../include/av_reader.h"
#include "../include/av_decoder.h"
#include "../include/av_encoder.h"
#include "../include/av_writer.h"

extern "C" {
#define __STDC_CONSTANT_MACROS
#include <libavdevice/avdevice.h>
}

int main(int argc, char **argv) {
    avdevice_register_all();

    std::cout << "Hi!" << std::endl;

    try {
        //TODO:
        std::cout << "//TODO: live streaming" << std::endl;

    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "Bye!" << std::endl;
    return 0;
}
