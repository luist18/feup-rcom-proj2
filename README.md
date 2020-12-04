# feup-rcom-proj2

[![GitHub license](https://img.shields.io/github/license/luist18/feup-rcom-proj2?color=blue)](https://github.com/luist18/feup-rcom-proj2/blob/master/LICENSE)

This repository comprises the second part of the Computer Networks course unit project. The goal was to create a C application to download files from an FTP server.

## Project description

This project emulates the process of retrieving a file from an FTP server as described below using `telnet`. The program creates two socket connections and executes a bunch of instructions to download a file.

### Using telnet

The following instructions retrieve a file from an FTP server using `telnet`.

**Opening first connection**

```bash
> telnet <server> <port>
> user anonymous          # or specific user
> pass whatever           # or specific password
> pasv
```

At this point the connection should send 6 bytes, the first 4 are the IP and the last 2 bytes the port in the format `b1 * 256 + b2` (where `b1` is the first byte and `b2` the second byte) of the server.

**Opening second connection**

The server and the port are the data returned from the first connection.

```bash
> telnet <server> <port>
```

Back in the first connection:

```bash
> retr <path to file>
```

The file content is sent to the second connection.

## Compiling

Run make in the root directory of the repository and the binary executable file is placed inside a bin directory in the repository root.

## Running

To run the program use:

```bash
download <url>
```

* the url should be in the format ftp://[\<user>:<password\>@]\<host>/\<url-path>

## Documentation

The documentation is generated automatically with doxygen and can be accessed [here](https://luist18.github.io/feup-rcom-proj2/).

### Disclaimer

This repository contains the **C** solution for the problem. Note that it might contain errors and should not be used as a solution for anyone besides the authors.

### License

[MIT](https://opensource.org/licenses/MIT)
