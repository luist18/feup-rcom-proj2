# Experience 1: configure an IP network

The objective of this experience is to connect two computers (*tux1* and *tux4*) using a switch and the ethernet ports.

## Plan

Configuring *tux1*:

```bash
ifconfig eth0 172.16.20.1/24
ifconfig eth0 up

route add -net 172.16.20.0/24 gw 172.16.20.254
```

Configuring *tux4*:

```bash
ifconfig eth0 172.16.20.254/24
ifconfig eth0 up

route add -net 172.16.20.0/24 gw 172.16.20.1
```

## Questions

### 1. What are ARP packets and what are they used for?

The ARP (Address Resolution Protocol) packets are used to get a link layer address, typically a MAC address, from an internet layer address, typically an IPv4 address.

Example from the experiment:

| Time        | Source            | Destination       | Protocol | Info                                    |
| ----------- | ----------------- | ----------------- | -------- | --------------------------------------- |
| 8.20531988  | HewlettP_5a:7d:12 | Netronix_50:3f:2c | ARP      | Who has 172.16.20.254? Tell 172.16.20.1 |
| 8.205406834 | Netronix_50:3f:2c | HewlettP_5a:7d:12 | ARP      | 172.16.20.254 is at 00:08:54:50:3f:2c   |

### 2. What are the MAC and IP addresses of ARP packets and why?


### 3. What packets does the ping command generate?
### 4. What are the MAC and IP addresses of the ping packets?
### 5. How to determine if a receiving Ethernet frame is ARP, IP, ICMP?
### 6. How to determine the length of a receiving frame?
### 7. What is the loopback interface and why is it important?
