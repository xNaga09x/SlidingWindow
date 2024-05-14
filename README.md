Sliding Window Protocol Simulation

Description:

The Sliding Window Protocol Simulation is a C++ application that simulates the transmission of packets from a source to a destination using a sliding window protocol. The protocol ensures reliable data transmission over an unreliable communication channel by implementing mechanisms for packet retransmission and acknowledgement.

Features:

1.Packet Transmission:

Packets are transmitted from the source to the destination in a sequential manner.
Each packet is numbered for identification purposes.

2.Sliding Window:

The sliding window represents the range of packets that can be transmitted and acknowledged at any given time.
The window slides dynamically based on acknowledgements received and timeouts encountered.

3.Error Handling:

Packets may fail to reach their destination due to random packet loss or acknowledgement loss.
If a packet fails to reach the destination or an acknowledgement is lost, the source retransmits the packet after a timeout period.

4.Acknowledgement Handling:

The destination acknowledges the receipt of packets.
If an acknowledgement is lost, the source retransmits the packet associated with the lost acknowledgement after a timeout period.

5.Window Management:

The window slides to the right as acknowledgements are received, allowing new packets to be transmitted.
If acknowledgements are lost or packets fail to reach the destination, the window remains fixed until the issue is resolved.

6.Timeout Mechanism:

If a packet or acknowledgement is lost, a timeout mechanism triggers packet retransmission or acknowledgement retransmission after a predefined timeout period.

7.Destination Buffer:

The destination maintains a buffer to store received packets.
Packets are sorted in the order they are received to ensure data integrity.

8.Source and Destination Memory:

Both the source and destination retain information about transmitted packets and received acknowledgements.
Retransmission decisions are made based on this stored information.

The Sliding Window Protocol Simulation provides a realistic environment for studying and understanding the behavior of sliding window protocols in data communication. Through dynamic window management, error handling mechanisms, and packet retransmission strategies, the simulation demonstrates the principles of reliable data transmission over unreliable channels.
