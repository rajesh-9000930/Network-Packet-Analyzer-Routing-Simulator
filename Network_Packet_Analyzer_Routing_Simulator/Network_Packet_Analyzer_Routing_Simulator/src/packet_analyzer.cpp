#include "packet_analyzer.hpp"

#include <cctype>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace {
std::uint16_t read16(const std::vector<std::uint8_t>& b, std::size_t i) {
    return static_cast<std::uint16_t>((static_cast<std::uint16_t>(b[i]) << 8) | b[i + 1]);
}

std::string ipv4At(const std::vector<std::uint8_t>& b, std::size_t i) {
    std::ostringstream out;
    out << static_cast<unsigned>(b[i]) << '.'
        << static_cast<unsigned>(b[i + 1]) << '.'
        << static_cast<unsigned>(b[i + 2]) << '.'
        << static_cast<unsigned>(b[i + 3]);
    return out.str();
}
}

std::vector<std::uint8_t> PacketAnalyzer::parseHex(const std::string& hex) {
    std::string compact;
    for (unsigned char c : hex) {
        if (std::isspace(c) || c == ':' || c == '-') continue;
        if (!std::isxdigit(c)) throw std::invalid_argument("Input contains a non-hexadecimal character.");
        compact.push_back(static_cast<char>(c));
    }
    if (compact.empty() || compact.size() % 2 != 0)
        throw std::invalid_argument("Hex input must contain a non-empty, even number of digits.");

    std::vector<std::uint8_t> bytes;
    bytes.reserve(compact.size() / 2);
    for (std::size_t i = 0; i < compact.size(); i += 2) {
        const auto value = static_cast<unsigned>(std::stoul(compact.substr(i, 2), nullptr, 16));
        bytes.push_back(static_cast<std::uint8_t>(value));
    }
    return bytes;
}

PacketInfo PacketAnalyzer::analyzeIPv4(const std::vector<std::uint8_t>& b) {
    if (b.size() < 20) throw std::invalid_argument("Packet is too short for a minimum IPv4 header.");

    const unsigned version = b[0] >> 4;
    const unsigned ihlWords = b[0] & 0x0F;
    const std::size_t headerBytes = ihlWords * 4U;

    if (version != 4) throw std::invalid_argument("Packet is not IPv4.");
    if (ihlWords < 5) throw std::invalid_argument("Invalid IPv4 header length.");
    if (b.size() < headerBytes) throw std::invalid_argument("Truncated IPv4 header.");

    const std::uint16_t totalLength = read16(b, 2);
    if (totalLength < headerBytes) throw std::invalid_argument("IPv4 total length is smaller than its header.");
    if (b.size() < totalLength) throw std::invalid_argument("Packet data is shorter than the IPv4 total length.");

    PacketInfo info;
    info.sourceIp = ipv4At(b, 12);
    info.destinationIp = ipv4At(b, 16);
    info.ttl = b[8];
    info.headerLength = static_cast<std::uint8_t>(headerBytes);
    info.totalLength = totalLength;

    switch (b[9]) {
        case 1: info.protocol = "ICMP"; break;
        case 6: info.protocol = "TCP"; break;
        case 17: info.protocol = "UDP"; break;
        default: info.protocol = "Unknown (" + std::to_string(b[9]) + ")"; break;
    }

    // Fragment offset is in the lower 13 bits. Only parse transport ports in the first fragment.
    const std::uint16_t fragmentField = read16(b, 6);
    const bool firstFragment = (fragmentField & 0x1FFFU) == 0;
    const std::size_t transportOffset = headerBytes;

    if (firstFragment && (b[9] == 6 || b[9] == 17)) {
        const std::size_t required = b[9] == 6 ? 20U : 8U;
        if (totalLength >= headerBytes + required && b.size() >= transportOffset + 4) {
            info.sourcePort = read16(b, transportOffset);
            info.destinationPort = read16(b, transportOffset + 2);
            info.hasPorts = true;
        }
    }
    return info;
}
