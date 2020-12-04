#ifndef CONNECTION_H
#define CONNECTION_H

#include "util.h"

/**
 * @brief Opens a socket connection with an hostname and port.
 * 
 * @param hostname  the hostname
 * @param port      the port
 * @return 0 if succeeded, any other number otherwise
 */
int open_socket(char *hostname, int port);

/**
 * @brief Opens a connection with an hostname and port.
 * 
 * @param hostname  the hostname
 * @param port      the port
 * @return 0 if succeeded, any other number otherwise 
 */
int open_connection(char *hostname, int port);

/**
 * @brief Send a message.
 * 
 * @param socket_fd   the file descriptor of the socket
 * @param message     the message
 * @return 0 if succeeded, any other number otherwise 
 */
int send_to(int socket_fd, char *message);

/**
 * @brief Reads a message from the socket.
 * 
 * @param socket_fd   the file descriptor of the socket
 * @param message     the message
 * @return 0 if succeeded, any other number otherwise  
 */
int read_from(int socket_fd, char *message);

/**
 * @brief Logs in an user (or anonymous login) in the socket.
 * 
 * @param socket_fd     the file descriptor of the socket
 * @param server_access the ftp_server_access_t struct
 * @return 0 if succeeded, any other number otherwise  
 */
int login(int socket_fd, ftp_server_access_t server_access);

/**
 * @brief Sets the connection to passive mode.
 * 
 * @param socket_fd   the file descriptor of the socket
 * @return 0 if succeeded, any other number otherwise  
 */
int pasv_mode(int socket_fd);

/**
 * @brief Retrieves a file from the connection.
 * 
 * @param socket_fd     the file descriptor of the socket
 * @param server_access the ftp_server_access_t struct
 * @return 0 if succeeded, any other number otherwise  
 */
int retrieve_file(int socket_fd, ftp_server_access_t server_access);

/**
 * @brief Saves the file retrieved.
 * 
 * @param socket_fd     the file descriptor of the socket
 * @param server_access the ftp_server_access_t struct
 * @return 0 if succeeded, any other number otherwise  
 */
int save_file(int socket_fd, ftp_server_access_t server_access);

/**
 * @brief Disconnects the socket.
 * 
 * @param socket_fd   the file descriptor of the socket
 * @return 0 if succeeded, any other number otherwise
 */
int disconnect(int socket_fd);

#endif