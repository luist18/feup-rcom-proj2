#ifndef CONNECTION_H
#define CONNECTION_H

#include "util.h"

int open_socket(char *hostname, int port);

int open_connection(char *hostname, int port);

int send_to(int socket_fd, char *message);

int read_from(int socket_fd, char *message);

int login(int socket_fd, ftp_server_access_t server_access);

int pasv_mode(int socket_fd);

int retrieve_file(int socket_fd, ftp_server_access_t server_access);

int save_file(int socket_fd, ftp_server_access_t server_access);

#endif