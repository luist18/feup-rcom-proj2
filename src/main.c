#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "connection.h"
#include "util.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: download ftp://[<user>:<password>@]<host>/<url-path>\n");
        exit(1);
    }

    ftp_server_access_t server_access;

    if (get_server_access(argv[1], &server_access)) {
        fprintf(stderr, "Invalid format. Usage: download ftp://[<user>:<password>@]<host>/<url-path>\n");
        exit(2);
    }

    ip_info_t ip_info;

    if (get_ip(server_access.connection_info.hostname, &ip_info)) {
        fprintf(stderr, "Invalid hostname\n");
        exit(3);
    }

    int fd;

    if ((fd = open_connection(ip_info.ip, 21)) < 0) {
        fprintf(stderr, "Could not establish connection with hostname\n");
        exit(4);
    }

    printf("Connection established.\n");

    if (login(fd, server_access)) {
        fprintf(stderr, "Could not login\n");
        exit(5);
    }

    printf("Login successfully.\n");

    int data_fd;

    if ((data_fd = pasv_mode(fd)) < 0) {
        fprintf(stderr, "Could not enter passive mode\n");
        exit(6);
    }

    printf("Connection established with data connection.\n");

    exit(0);
}
