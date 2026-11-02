#include "routing.hpp"

#include <algorithm>
#include <functional>
#include <stdexcept>
#include <limits>
#include <queue>
#include <unordered_map>

void RoutingSimulator::addLink(const std::string& from, const std::string& to, int cost) {
    if (cost < 0) throw std::invalid_argument("Dijkstra routing requires non-negative link costs.");
    graph_[from].push_back({to, cost});
    graph_[to].push_back({from, cost});
}

RouteResult RoutingSimulator::shortestPath(const std::string& source, const std::string& destination) const {
    using Entry = std::pair<int, std::string>;
    const int infinity = std::numeric_limits<int>::max();

    std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> queue;
    std::unordered_map<std::string, int> distance;
    std::unordered_map<std::string, std::string> previous;

    for (const auto& node : graph_) distance[node.first] = infinity;
    if (distance.find(source) == distance.end() || distance.find(destination) == distance.end())
        return {};

    distance[source] = 0;
    queue.push({0, source});

    while (!queue.empty()) {
        const auto [cost, node] = queue.top();
        queue.pop();
        if (cost != distance[node]) continue;
        if (node == destination) break;

        const auto it = graph_.find(node);
        if (it == graph_.end()) continue;

        for (const auto& edge : it->second) {
            const auto& neighbor = edge.first;
            const int nextCost = cost + edge.second;
            if (nextCost < distance[neighbor]) {
                distance[neighbor] = nextCost;
                previous[neighbor] = node;
                queue.push({nextCost, neighbor});
            }
        }
    }

    if (distance[destination] == infinity) return {};

    RouteResult result;
    result.reachable = true;
    result.totalCost = distance[destination];

    for (std::string at = destination;; at = previous.at(at)) {
        result.path.push_back(at);
        if (at == source) break;
    }
    std::reverse(result.path.begin(), result.path.end());
    return result;
}

RoutingSimulator RoutingSimulator::sampleTopology() {
    RoutingSimulator network;
    network.addLink("A", "B", 4);
    network.addLink("A", "C", 2);
    network.addLink("B", "C", 1);
    network.addLink("B", "D", 5);
    network.addLink("C", "D", 8);
    network.addLink("C", "E", 10);
    network.addLink("D", "E", 2);
    network.addLink("D", "F", 6);
    network.addLink("E", "F", 3);
    return network;
}
