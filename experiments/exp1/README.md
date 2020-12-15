# 1. Experience 1: configure an IP network

The objective of this experience is to connect two computers (*tux1* and *tux4*) using a switch and the ethernet ports.

## Table of Contents<!-- omit in toc -->

- [1. Experience 1: configure an IP network](#1-experience-1-configure-an-ip-network)
  - [1.1. Plan](#11-plan)
  - [1.2. Overview](#12-overview)
  - [1.3. References](#13-references)

***

## 1.1. Plan

Configuring *tux1*:

```bash
ifconfig eth0 up
ifconfig eth0 172.16.20.1/24

route add -net 172.16.20.0/24 gw 172.16.20.254
```

Configuring *tux4*:

```bash
ifconfig eth0 up
ifconfig eth0 172.16.20.254/24

route add -net 172.16.20.0/24 gw 172.16.20.1
```

***

## 1.2. Overview

The ARP (Address Resolution Protocol) packets are used to get a link layer address, typically a MAC address, from an internet layer address, typically an IPv4 address. (include example in report)

When testing the connectivity between the two *tux* computers with the `ping` command if the IP of *tux4* is not present in the ARP entry table of *tux1* then an ARP packet is sent to the broadcast channel asking for the MAC address of *tux4*. The packet is initially sent from *tux1* with an empty MAC address and the IP of *tux4*. Later, *tux4* identifies itself as the receptor of that packet and sends an ARP reply packet with its MAC address.

Example of ARP packets monitored in Wireshark:

| Time        | Source            | Destination       | Protocol | Info                                    |
| ----------- | ----------------- | ----------------- | -------- | --------------------------------------- |
| 8.20531988  | HewlettP_5a:7d:12 | Netronix_50:3f:2c | ARP      | Who has 172.16.20.254? Tell 172.16.20.1 |
| 8.205406834 | Netronix_50:3f:2c | HewlettP_5a:7d:12 | ARP      | 172.16.20.254 is at 00:08:54:50:3f:2c   |

Finally, the `ping` command is able to send ICMP packets. The packets sent from *tux1* to *tux4* are ICMP Echo (ping) requests and in the backwards order *tux4* send to *tux1* ICMP Echo (ping) replies.

The distinction between an ARP and IP frame can be done by looking at the MAC header of the Ethernet Type II frames [1]. The MAC header has 14 bytes. The first 6 bytes are the MAC address of the receptor, the next 6 bytes are the MAC address of the source and the last 2 the type. If the type is `0x0800` or `0x86DD` then its an IPv4 or IPv6 frame, respectively. On the other hand, if the type is `0x0806` then its and ARP frame.

Since ICMP is a protocol of IP it can be identified by looking at the header of the IP packet [2], the protocol type is located in the 10th octet and the length in the 3rd and 4th octets. The protocol type of an ICMP packet is `0x01`. The length located in the 3rd and 4th octets is the total length of the packet, including header and data.

Example of an ICMP IP packet header:

`45 00 00 54 03 25 40 00 40 01 b6 64 ac 10 14 01 ac 10 14 fe`

Protocol: `0x01` Total length: `0x0054`, which in decimal is 84 (bytes) 20 for the header and 64 for data.

> **Note:** the first octet of the IP packet header is divided into two 4 bit fields. The second 4-bit field represents the number of words (32 bits) in the header. Since it is 5, 5 x 32 = 160 bits which are 20 bytes used in the packet header.

TODO Question 7: What is the loopback interface and why is it important?

## 1.3. References

- [1] https://en.wikipedia.org/wiki/Ethernet_frame
- [2] https://en.wikipedia.org/wiki/IPv4
