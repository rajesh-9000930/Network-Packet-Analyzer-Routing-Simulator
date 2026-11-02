#include "packet_analyzer.hpp"
#include "routing.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

void printPacket(const PacketInfo& p) {
    std::cout << "\n=== IPv4 Packet Analysis ===\n"
              << "Source IP       : " << p.sourceIp << '\n'
              << "Destination IP  : " << p.destinationIp << '\n'
              << "Protocol        : " << p.protocol << '\n'
              << "TTL             : " << static_cast<unsigned>(p.ttl) << '\n'
              << "Header length   : " << static_cast<unsigned>(p.headerLength) << " bytes\n"
              << "Total length    : " << p.totalLength << " bytes\n";
    if (p.hasPorts) {
        std::cout << "Source port     : " << p.sourcePort << '\n'
                  << "Destination port: " << p.destinationPort << '\n';
    }
}

void printRoute(const RouteResult& route) {
    if (!route.reachable) {
        std::cout << "No route found. Check the node names and topology.\n";
        return;
    }
    std::cout << "Shortest route  : ";
    for (std::size_t i = 0; i < route.path.size(); ++i) {
        if (i) std::cout << " -> ";
        std::cout << route.path[i];
    }
    std::cout << "\nTotal path cost : " << route.totalCost << '\n';
}

void usage(const char* app) {
    std::cout << "Network Packet Analyzer & Routing Simulator\n\n"
              << "Usage:\n"
              << "  " << app << " demo\n"
              << "  " << app << " analyze \"<hex packet bytes>\"\n"
              << "  " << app << " route <source-node> <destination-node>\n";
}

int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            usage(argv[0]);
            return 0;
        }

        const std::string command = argv[1];
        if (command == "analyze") {
            if (argc < 3) throw std::invalid_argument("Please provide packet bytes in hexadecimal.");
            const auto bytes = PacketAnalyzer::parseHex(argv[2]);
            printPacket(PacketAnalyzer::analyzeIPv4(bytes));
        } else if (command == "route") {
            if (argc != 4) throw std::invalid_argument("Route command requires source and destination nodes.");
            const auto network = RoutingSimulator::sampleTopology();
            printRoute(network.shortestPath(argv[2], argv[3]));
        } else if (command == "demo") {
            const std::string sample =
                "45 00 00 28 1c 46 40 00 40 06 b1 e6 "
                "c0 a8 01 0a c0 a8 01 01 "
                "30 39 00 50 00 00 00 01 00 00 00 00 "
                "50 02 20 00 91 7c 00 00";
            printPacket(PacketAnalyzer::analyzeIPv4(PacketAnalyzer::parseHex(sample)));
            std::cout << "\n=== Routing Simulation ===\n";
            printRoute(RoutingSimulator::sampleTopology().shortestPath("A", "F"));
        } else if (command == "help" || command == "--help" || command == "-h") {
            usage(argv[0]);
        } else {
            usage(argv[0]);
            return 1;
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }
    return 0;
}
