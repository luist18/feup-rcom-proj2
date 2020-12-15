# 1. Experience 1: configure a router in Linux

The objective of this experience is to create a virtual router using the CISCO switch.

## Table of Contents<!-- omit in toc -->

- [1. Experience 1: configure a router in Linux](#1-experience-1-configure-a-router-in-linux)
  - [1.1. Plan](#11-plan)
  - [1.2. Overview](#12-overview)

***

## 1.1. Plan

Configuring *tux4*:

```bash
ifconfig eth1 up
ifconfig eth1 172.16.21.253/24
route add default gw 172.16.21.254

echo 1 > /proc/sys/net/ipv4/ip_forward
echo 0 >  /proc/sys/net/ipv4/icmp_echo_ignore_broadcasts
```

Configuring the *switch*:

```bash
configure terminal
interface fastethernet 0/4
switchport mode access
switchport access vlan 21
end
```

Configuring *tux2*:
```bash
route add -net 172.16.20.0/24 gw 172.16.21.253
```

Configuring *tux3*:
```bash
route add -net 172.16.21.0/24 gw 172.16.20.254
```

***

## 1.2. Overview

TODO