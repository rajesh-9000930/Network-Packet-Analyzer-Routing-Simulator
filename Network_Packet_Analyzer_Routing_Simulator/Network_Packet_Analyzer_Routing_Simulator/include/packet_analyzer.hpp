#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct PacketInfo {
    std::string sourceIp;
    std::string destinationIp;
    std::string protocol;
    std::uint8_t ttl{};
    std::uint8_t headerLength{};
    std::uint16_t totalLength{};
    bool hasPorts{false};
    std::uint16_t sourcePort{};
    std::uint16_t destinationPort{};
};

class PacketAnalyzer {
public:
    static std::vector<std::uint8_t> parseHex(const std::string& hex);
    static PacketInfo analyzeIPv4(const std::vector<std::uint8_t>& bytes);
};
