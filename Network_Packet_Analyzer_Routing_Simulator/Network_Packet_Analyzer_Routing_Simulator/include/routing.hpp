#pragma once

#include <string>
#include <unordered_map>
#include <vector>

struct RouteResult {
    bool reachable{false};
    int totalCost{};
    std::vector<std::string> path;
};

class RoutingSimulator {
public:
    void addLink(const std::string& from, const std::string& to, int cost);
    RouteResult shortestPath(const std::string& source, const std::string& destination) const;
    static RoutingSimulator sampleTopology();

private:
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> graph_;
};
