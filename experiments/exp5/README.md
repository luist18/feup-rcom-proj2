# 1. Experience 5: DNS

In this experiment it was necessary to configure the DNS (Domais Name System) in each _tux_. A DNS server, in this case services.netlab.fe.up.pt, contains a database of public IP addresses and their respective hostnames. It is used to translate the hostnames to their respective IP addresses. 

## Table of Contents<!-- omit in toc -->

- [1. Experience 5: DNS](#1-experience-5-DNS)
  - [1.1. Plan](#11-plan)
  - [1.2. Overview](#12-overview)

***

## 1.1. Plan

Configuring the DNS in each *tux*
```bash
echo $'search netlab.fe.up.pt\nnameserver 172.16.1.1' > /etc/resolv.conf
```

## 1.2. Overview


In order to configure the DNS service, it is necessary to change the resolv.conf file, which is present in the etc/ directory in the host TUX. 
That file will need to have the following information:  
    
    search netlab.fe.up.pt
    nameserver 172.16.1.1

Where __netlab.fe.up.pt__ is the name of the DNS server and 172.16.1.1 its IP address. 

Initially, the host sends a packet to the server (line 8), which contains the desired _hostname_, asking for its IP address.  
The server responds with a packet that contains the IP address of the _hostname_ (line 11).


![](./snippet.png)
