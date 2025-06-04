#ifndef SAMPLE_PACKET_HPP
#define SAMPLE_PACKET_HPP

#include <array>
#include <cstdint>

struct SamplePacket {
    std::array<uint16_t,3> ticks;
    std::array<uint16_t,3> bpm;
};

#endif