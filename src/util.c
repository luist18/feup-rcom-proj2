#include "util.h"

#include <regex.h>
#include <stdio.h>
#include <string.h>

int get_server_access(char* string, ftp_server_access_t* access) {
    regex_t regex;
    regmatch_t captured_groups[8];

    int value;

    // Function call to create regex
    value = regcomp(&regex, "ftp://((.*):(.*)@([^/]*)/)?(([^:/]*/)?([^:]*))$", REG_EXTENDED);

    if (regexec(&regex, string, 8, captured_groups, 0) != 0)
        return 1;

    if (captured_groups[1].rm_eo - captured_groups[1].rm_so) {
        char user[256], pass[256], host[256], path[256];

        _read_capture_group(captured_groups, 2, string, user);
        _read_capture_group(captured_groups, 3, string, pass);
        _read_capture_group(captured_groups, 4, string, host);
        _read_capture_group(captured_groups, 5, string, path);

        ftp_connection_info_t connection_info;

        connection_info.connection_type = FTP_SIGNEDCON;
        strcpy(connection_info.user, user);
        strcpy(connection_info.pass, pass);
        strcpy(connection_info.hostname, host);
        strcpy(access->path, path);
        memcpy(&(access->connection_info), &connection_info, sizeof(ftp_connection_info_t));
    } else {
        char host[256], path[256];

        _read_capture_group(captured_groups, 6, string, host);
        _read_capture_group(captured_groups, 7, string, path);

        ftp_connection_info_t connection_info;

        host[strlen(host) - 1] = '\0';

        connection_info.connection_type = FTP_ANONCON;
        strcpy(connection_info.user, "anonymous");
        strcpy(connection_info.pass, "whatever");
        strcpy(connection_info.hostname, host);
        strcpy(access->path, path);
        memcpy(&(access->connection_info), &connection_info, sizeof(ftp_connection_info_t));
    }

    return 0;
}

void print_server_access(ftp_server_access_t* access) {
    printf("Connection information\n\n");
    if (access->connection_info.connection_type == FTP_ANONCON) {
        printf("\tConnection type: anonymous\n");
        printf("\tUser: %s\n", access->connection_info.user);
        printf("\tHostname: %s\n", access->connection_info.hostname);
        printf("\tPath: %s\n", access->path);
    } else {
        printf("\tConnection type: signed\n");
        printf("\tUser: %s\n", access->connection_info.user);
        printf("\tPassword: %s\n", access->connection_info.pass);
        printf("\tHostname: %s\n", access->connection_info.hostname);
        printf("\tPath: %s\n", access->path);
    }
}

void _read_capture_group(regmatch_t* groups, size_t group, char* string, char* output) {
    char* p = string + groups[group].rm_so;
    size_t l = groups[group].rm_eo - groups[group].rm_so;

    strncpy(output, p, l);
    output[l] = '\0';
}

int get_ip(char* ip, ip_info_t* ip_info) {
    struct hostent* h;

    if ((h = gethostbyname(ip)) == NULL)
        return 1;

    strcpy(ip_info->hostname, h->h_name);
    strcpy(ip_info->ip, inet_ntoa(*((struct in_addr*)h->h_addr)));

    return 0;
}

int get_filename(char* path, char* filename) {
    const char path_delimiter[] = "/";

    char* token = strtok(path, path_delimiter);
    char* prev_token;

    while (token != NULL) {
        prev_token = token;

        token = strtok(NULL, path_delimiter);
    }

    strcpy(filename, prev_token);

    return 0;
}