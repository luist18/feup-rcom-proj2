# 1. Experience 4: configure a commercial router and implement NAT

The objective of this experience is to configure a commercial router and implement NAT. 

## Table of Contents<!-- omit in toc -->

- [1. Experience 4: configure a commercial router and implement NAT](#1-experience-4-configure-a-commercial-router-and-implement-nat)
  - [1.1. Plan](#11-plan)
  - [1.2. Overview](#12-overview)
  - [1.3. Questions](#13-questions)

***

## 1.1. Plan

***

## 1.2. Overview

TODO

***
## 1.3 Questions

### How to configure a static route in a commercial router?

Initially, we need to connect the port T3 to the port S0 of the TUX that we want to be connected to the router. Subsequently, we need to connect the port T4 to the router console.  

Aftewards, we need to access the GTKTerm of the chosen TUX and execute the following commands:
        
    > configure terminal
    > ip route [destination route ip] [mask] [ip gateway]
    > exit


### What are the paths followed by the packets in the experiments carried out and why?

In case the route exists, the packets will use that same route. Otherwise, the packets will follow the default route (to the router), the router will inform that TUX4 exists and the packets will be sent to it. 

### How to configure NAT in a commercial router?  

To configure NAT in a commercial router, we need to execute the following commands from the GTKTerm of the chosen TUX.

    conf t
    interface gigabitethernet 0/0 *
    ip address 172.16.y1.254 255.255.255.0
    no shutdown
    ip nat inside
    exit

    interface gigabitethernet 0/1*
    ip address 172.16.1.y9 255.255.255.0
    no shutdown
    ip nat outside
    exit

    ip nat pool ovrld 172.16.1.y9 172.16.1.y9 prefix 24
    ip nat inside source list 1 pool ovrld overload

    access-list 1 permit 172.16.y0.0 0.0.0.7
    access-list 1 permit 172.16.y1.0 0.0.0.7

    ip route 0.0.0.0 0.0.0.0 172.16.1.254
    ip route 172.16.y0.0 255.255.255.0 172.16.y1.253
    end



### What does NAT do?

NAT, which stands for Network Address Translation, allows a single device, such as a router, to act as an agent between the public network and a local network, meaning that only a single unique IP address is required to represent an entire group of computers to anything outside their network. 
 
With that said, the implementation of NAT had as a goal to allow the communication between the computers of the network we created with external networks. Since it's a private network, the IPs would never be recognized outside the network.
