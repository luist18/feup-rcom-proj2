# 1. Experience 6: TCP Connections

The objective of this experience is to (...)

## Table of Contents<!-- omit in toc -->

- [1. Experience 6: TCP Connections](#1-experience-6-TCP-Connections)
  - [1.1. Plan](#11-plan)
  - [1.2. Overview](#12-overview)
  - [1.3. Questions](#13-questions)

***

## 1.1. Plan

***

## 1.2. Overview

TODO


## 1.3 Questions

### How many TCP connections are opened by your ftp application?

Our FTP application opens two TCP connections: one for control, to send the FTP commands to the server (and receive the responses) and one to receive the data sent by the server.


### In what connection is transported the FTP control information?
The FTP control information is transported in the _control_ connection, i.e. the one responsible for sending the commands to the server.


### What are the phases of a TCP connection?
A TCP connection has three fases: establishment of the connection, data transfer and connection termination.


### How does the ARQ TCP mechanism work? What are the relevant TCP fields? What relevant information can be observed in the logs?

TCP (Transmission Control Protocol) utilizes the ARQ (Automatic Repeat Request) mechanism with the "Sliding Window" method. That way, it uses:
- __acknowledgment numbers__, which are present in one of the fields of the messages sent by the receptor which indicate which frame was received correctly;
- __window size__, which indicates the range of packets that the emitter can send;
- __sequence number__, which represents the number of the frame to be sent. 

![](./snippet.png)



### How does the TCP congestion control mechanism work? What are the relevant fields. How did the throughput of the data connection evolve along the time? Is it according the TCP congestion control mechanism?


### Is the throughput of a TCP data connections disturbed by the appearance of a second TCP connection? How?
