# Network Packet Analyzer and Intelligent Routing Simulator

## Overview

The **Network Packet Analyzer and Intelligent Routing Simulator** is a C++17-based networking project designed to analyze IPv4 packet data and simulate intelligent network routing.

The application extracts and interprets important information from IPv4 packet headers, identifies network protocols, retrieves TCP/UDP port details, and calculates optimal network paths using Dijkstra's shortest-path algorithm.

This project demonstrates practical concepts of computer networking, packet structure analysis, routing algorithms, and systems programming.

## Key Features

- **IPv4 Packet Analysis:** Parses IPv4 packet data provided in hexadecimal format.
- **IP Address Extraction:** Identifies source and destination IPv4 addresses.
- **Protocol Identification:** Detects TCP, UDP, and ICMP protocols.
- **Header Information Analysis:** Extracts TTL, header length, and total packet length.
- **Port Number Extraction:** Retrieves source and destination port numbers from TCP and UDP packets.
- **Intelligent Routing Simulation:** Uses Dijkstra's algorithm to determine the shortest path between network nodes.
- **Route Cost Calculation:** Calculates the total cost of the selected network path.
- **Input Validation:** Handles invalid or incomplete packet data.

## Technologies Used

| Technology | Purpose |
|---|---|
| C++17 | Core application development |
| Data Structures | Packet processing and graph representation |
| Dijkstra's Algorithm | Shortest-path routing |
| CMake | Build configuration |
| Git & GitHub | Version control and project management |

## Project Architecture

The project is organized into separate modules to improve code readability, maintainability, and reusability.

```text
Network-Packet-Analyzer-and-Intelligent-Routing-Simulator/
│
├── include/
│   ├── packet_analyzer.hpp
│   └── routing.hpp
│
├── src/
│   ├── main.cpp
│   ├── packet_analyzer.cpp
│   └── routing.cpp
│
├── samples/
│   └── sample_ipv4_tcp.hex
│
├── tests/
│   └── manual_test_cases.md
│
├── CMakeLists.txt
├── README.md
└── .gitignore
```

## How It Works

### 1. Packet Input
The application accepts IPv4 packet data in hexadecimal format.

### 2. Packet Parsing
The packet analyzer processes the input and extracts:
- Source IPv4 address
- Destination IPv4 address
- Protocol type
- Time to Live (TTL)
- IP header length
- Total packet length

### 3. Protocol Analysis
The application identifies the protocol and extracts TCP or UDP source and destination port numbers when available.

### 4. Routing Simulation
The routing module represents the network as a weighted graph. Dijkstra's shortest-path algorithm calculates the optimal route between the selected source and destination nodes.

### 5. Result Display
The application displays the extracted packet information and the calculated routing path with its total cost.

## Installation and Execution

### Prerequisites

- C++17-compatible compiler
- CMake 3.16 or later
- Git

### Step 1: Clone the Repository

```bash
git clone https://github.com/YOUR-USERNAME/Network-Packet-Analyzer-and-Intelligent-Routing-Simulator.git
```

### Step 2: Navigate to the Project Directory

```bash
cd Network-Packet-Analyzer-and-Intelligent-Routing-Simulator
```

### Step 3: Create a Build Directory

```bash
cmake -S . -B build
```

### Step 4: Build the Project

```bash
cmake --build build
```

### Step 5: Run the Application

**Windows:**

```bash
.\build\Debug\network_simulator.exe
```

If your build configuration places the executable directly inside `build`, use:

```bash
.\build\network_simulator.exe
```

**Linux:**

```bash
./build/network_simulator
```
** Sample Output

```text
NETWORK PACKET ANALYZER

Source IP      : 192.168.1.10
Destination IP : 192.168.1.1
Protocol       : TCP
TTL            : 64
Source Port    : 12345
Destination Port: 80

INTELLIGENT ROUTING SIMULATOR

Shortest Path  : A -> C -> B -> D -> E -> F
Total Cost     : 13
```

*The output above illustrates the included sample packet and routing demonstration.*

## Learning Outcomes

Through this project, the following concepts are demonstrated:

- Understanding IPv4 packet structure and network protocols.
- Implementing packet parsing using C++.
- Working with TCP, UDP, and ICMP protocol concepts.
- Applying graph data structures to network routing.
- Implementing Dijkstra's shortest-path algorithm.
- Organizing a modular C++ application using header and source files.
- Building and managing projects using CMake and Git.

## Current Scope and Limitations

This is an educational packet analysis and routing simulation project.

- Packet analysis uses hexadecimal packet data supplied to the application.
- It does not currently capture live network traffic.
- It does not modify actual network routing tables.
- It does not transmit or intercept network packets.
- It does not implement production routing protocols such as BGP or OSPF.

## Future Enhancements

- Integrate live packet capture using libraries such as libpcap or Npcap.
- Add network traffic statistics and protocol distribution analysis.
- Develop a graphical user interface for packet visualization.
- Extend routing simulation with additional routing algorithms.
- Explore dynamic routing protocol concepts such as OSPF and BGP.


.
