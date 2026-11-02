# Manual test cases

Build the project before running these cases.

1. `network_analyzer demo`
   - Expected: IPv4 source `192.168.1.10`, destination `192.168.1.1`, protocol TCP,
     source port 12345, destination port 80; route A -> C -> B -> D -> E -> F or another
     minimum-cost route with total cost 13.
2. `network_analyzer route A F`
   - Expected: reachable route with total cost 13.
3. `network_analyzer route A Z`
   - Expected: no route found.
4. `network_analyzer analyze "not-hex"`
   - Expected: a clear input validation error.
5. `network_analyzer analyze "45 00"`
   - Expected: packet-too-short error.

Note: The sample packet is a deliberately small educational IPv4/TCP header example.
The tool validates the IPv4 header and extracts selected fields; it is not a full protocol
conformance validator.
