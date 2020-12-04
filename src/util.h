#ifndef UTIL_H
#define UTIL_H

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define CAPTURED_GROUPS 6

/**
 * @brief Enum to define an FTP connection type.
 */
typedef enum ftp_connection_type_t {
    FTP_ANONCON,   /* Anonymous connection */
    FTP_SIGNEDCON, /* Signed connection */
} ftp_connection_type_t;

/**
 * @brief Information related to an FTP connection.
 */
typedef struct ftp_connection_info_t {
    char user[256];                        /* User of the connection. Null pointer if anonymous connection */
    char pass[256];                        /* Pass of the connection. Null pointer if anonymous connection */
    char hostname[256];                    /* User of the connection. Null pointer if anonymous connection */
    ftp_connection_type_t connection_type; /* Connection type */
} ftp_connection_info_t;

/**
 * @brief Information related to an FTP server access.
 */
typedef struct ftp_server_access_t {
    ftp_connection_info_t connection_info; /* Connection info */
    char path[256];                        /* Access path */
} ftp_server_access_t;

/**
 * @brief Information of the IP address.
 */
typedef struct ip_info_t {
    char hostname[256]; /* The hostname */
    char ip[256];       /* The IP */
} ip_info_t;

/**
 * @brief Gets the server access struct.
 * 
 * @param string    ftp url string
 * @param access    ftp_server_access_t struct pointer
 * @return 0 if succeeded, any other number otherwise
 */
int get_server_access(char* string, ftp_server_access_t* access);

/**
 * @brief Prints the server access struct information.
 * 
 * @param access    ftp_server_access_t struct pointer
 */
void print_server_access(ftp_server_access_t* access);

/**
 * @brief Reads a captured group from a regex.
 * 
 * @param groups    the groups
 * @param group     the group
 * @param string    the string
 * @param output    the captured group
 */
void _read_capture_group(regmatch_t* groups, size_t group, char* string, char* output);

/**
 * @brief Get the ip info struct.
 * 
 * @param ip        the ip
 * @param ip_info   the ip_info_t struct
 * @return 0 if succeeded, any other number otherwise
 */
int get_ip(char* ip, ip_info_t* ip_info);

/**
 * @brief Get the filename of a path.
 * 
 * @param path      the path
 * @param filename  the filename
 * @return 0 if succeeded, any other number otherwise
 */
int get_filename(char* path, char* filename);

#endif