# 1. Experience 1: implement two virtual LANs in a switch

The objective of this experience is to create a virtual lan using the CISCO switch.

## Table of Contents<!-- omit in toc -->

- [1. Experience 1: implement two virtual LANs in a switch](#1-experience-1-implement-two-virtual-lans-in-a-switch)
  - [1.1. Plan](#11-plan)
  - [1.2. Overview](#12-overview)

***

## 1.1. Plan

Configuring *tux2*:

```bash
ifconfig eth0 up
ifconfig eth0 172.16.21.1/24

route add -net 172.16.20.0/24 gw 172.16.21.254
```

Configuring both *vlans* (tux 2, 3, 4 are in port 2, 3 and 4 respectively):

```bash
configure terminal
vlan 20
end

configure terminal
interface fastethernet 0/3
switchport mode access
switchport access vlan 20
end

configure terminal
interface fastethernet 0/4
switchport mode access
switchport access vlan 20
end

configure terminal
vlan 21
end

configure terminal
interface fastethernet 0/2
switchport mode access
switchport access vlan 21
end
```

***

## 1.2. Overview

TODO