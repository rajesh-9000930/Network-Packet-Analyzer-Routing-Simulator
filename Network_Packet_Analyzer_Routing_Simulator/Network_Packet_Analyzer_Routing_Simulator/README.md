# Network Packet Analyzer & Intelligent Routing Simulator

A C++17 portfolio project demonstrating IPv4 packet parsing, TCP/UDP/ICMP protocol identification,
and shortest-path routing using Dijkstra's algorithm.

## Features

- Parse an IPv4 packet supplied as hexadecimal bytes.
- Validate basic IPv4 header properties and packet length.
- Display source/destination IPv4 addresses, protocol, TTL, header length and total length.
- Extract TCP/UDP source and destination ports when their headers are present.
- Simulate a network topology and calculate the lowest-cost route with Dijkstra's algorithm.
- Include a built-in demo and sample packet.

> **Scope and safety:** This is an educational packet parser and routing simulator. It does not
> capture live traffic, modify network routes, or transmit packets. It analyzes packet bytes
> supplied by the user. Live capture can be added later with libpcap/Npcap and appropriate
> permissions.

## Requirements

- C++17 compiler (GCC 9+, Clang 10+, or a recent MSVC)
- CMake 3.16+

## Build

### Linux / macOS

```bash
cmake -S . -B build
cmake --build build
```

### Windows (Visual Studio Build Tools)

```powershell
cmake -S . -B build
cmake --build build --config Release
```

## Run

The executable is named `network_analyzer` (Windows: `network_analyzer.exe`).

```bash
# Built-in packet + routing demonstration
./build/network_analyzer demo

# Analyze an IPv4 packet represented as hex bytes
./build/network_analyzer analyze "45 00 00 28 1c 46 40 00 40 06 b1 e6 c0 a8 01 0a c0 a8 01 01 30 39 00 50 00 00 00 01 00 00 00 00 50 02 20 00 91 7c 00 00"

# Find a route in the sample topology
./build/network_analyzer route A D
```

For a packet file, place one hex packet on a line and pass its contents as the `analyze` argument.
The sample is also available at `samples/sample_ipv4_tcp.hex`.

## Sample output

Packet analysis reports:
- IPv4 source and destination
- Protocol (TCP, UDP, ICMP, or numeric unknown)
- TTL, header length, total length
- TCP/UDP ports when present

Routing reports the route, total path cost, and each hop.

## Project structure

```text
include/
  packet_analyzer.hpp
  routing.hpp
src/
  main.cpp
  packet_analyzer.cpp
  routing.cpp
samples/
  sample_ipv4_tcp.hex
tests/
  manual_test_cases.md
CMakeLists.txt
README.md
```

## Resume description (use after building and testing)

**Network Packet Analyzer and Intelligent Routing Simulator**  
* C++17, IPv4, TCP/UDP/ICMP, Data Structures & Algorithms, Dijkstra's Algorithm, CMake, Git

- Built a C++17 utility to parse IPv4 packet headers and identify source/destination addresses and network protocols.
- Extracted TCP/UDP port information and validated packet header lengths and packet sizes.
- Implemented a graph-based routing simulator using Dijkstra's shortest-path algorithm to calculate minimum-cost paths.
- Added command-line workflows and test cases for packet parsing and route calculation.

Only claim features you have personally compiled, run, understood, and can explain in an interview.

## Suggested future enhancements

1. Add automated unit tests with GoogleTest or Catch2.
2. Add live packet capture using libpcap (Linux/macOS) or Npcap (Windows).
3. Add a topology editor and routing table updates.
4. Add OSPF/BGP concepts as educational simulations (not production protocol implementations).
5. Add performance benchmarks and CI with GitHub Actions.
