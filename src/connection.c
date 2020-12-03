#include "connection.h"

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "util.h"

#define MAX_SIZE 4096

int open_socket(char *hostname, int port) {
    int sockfd;
    struct sockaddr_in server_addr;
    int bytes;

    /*server address handling*/
    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(hostname);
    server_addr.sin_port = htons(port);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        exit(0);
    }
    if (connect(sockfd,
                (struct sockaddr *)&server_addr,
                sizeof(server_addr)) < 0) {
        perror("connect()");
        exit(0);
    }

    return sockfd;
}

int open_connection(char *hostname, int port) {
    char tmp_buffer[MAX_SIZE];

    int fd;
    if ((fd = open_socket(hostname, port)) < 0)
        return -1;

    read_from(fd, tmp_buffer);

    return fd;
}

int send_to(int socket_fd, char *message) {
    if ((write(socket_fd, message, strlen(message))) <= 0) {
        printf("%s: Could not send message\n", __func__);
        return 1;
    }

    return 0;
}

int read_from(int socket_fd, char *message) {
    FILE *stream = fdopen(socket_fd, "r");
    memset(message, 0, MAX_SIZE);

    // [3 digit code][space indicator of input][message]
    while (message[3] != ' ') {
        memset(message, 0, MAX_SIZE);
        message = fgets(message, MAX_SIZE, stream);
    }

    return 0;
}

int login(int socket_fd, ftp_server_access_t server_access) {
    char login_cmd[MAX_SIZE], pass_cmd[MAX_SIZE], tmp_buffer[MAX_SIZE];

    sprintf(login_cmd, "USER %s\n", server_access.connection_info.user);
    sprintf(pass_cmd, "PASS %s\n", server_access.connection_info.pass);

    if (send_to(socket_fd, login_cmd))
        return 1;

    read_from(socket_fd, tmp_buffer);

    if (send_to(socket_fd, pass_cmd))
        return 1;

    read_from(socket_fd, tmp_buffer);

    return 0;
}

int pasv_mode(int socket_fd) {
    char tmp_buffer[MAX_SIZE];

    if (send_to(socket_fd, "PASV\n"))
        return -1;

    read_from(socket_fd, tmp_buffer);

    int ip[4], port_array[2];

    if ((sscanf(tmp_buffer, "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d)", &ip[0], &ip[1], &ip[2], &ip[3], &port_array[0], &port_array[1])) < 0)
        return -1;

    int port = port_array[0] * 256 + port_array[1];

    char ip_address[256];

    sprintf(ip_address, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);

    return open_socket(ip_address, port);
}

int retrieve_file(int socket_fd, ftp_server_access_t server_access) {
    char retrieve_cmd[MAX_SIZE], tmp_buffer[MAX_SIZE];

    sprintf(retrieve_cmd, "retr %s\n", server_access.path);

    if (send_to(socket_fd, retrieve_cmd))
        return 1;

    read_from(socket_fd, tmp_buffer);

    return 0;
}

int save_file(int socket_fd, ftp_server_access_t server_access) {
    return 0;
}