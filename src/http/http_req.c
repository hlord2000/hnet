#include <string.h>
#include <stdio.h>

#include <http.h>
#include <http_req.h>

static int validate_request_method(char *data_received, size_t data_length) {
    if (data_received == NULL) {
        return -1;
    }

    if (data_length == NULL) {
        return -1;
    }

};

static int validate_request_path(char *data_received, size_t data_length) {
    if (data_received == NULL) {
        return -1;
    }
    
    if (data_length == NULL) {
        return -1;
    }

    if (strstr(data_received, "..") != NULL) {
        return -1;
    }
    if (strstr(data_received, "#") != NULL) {
        return -1;
    }
    if (strstr(data_received, "?") != NULL) {
        return -1;
    }
    char *path[512]; 
    
    strcpy(path, "./www", sizeof(path));
    strncat(path, data_received, sizeof(path));

    return 0; 
};

static int validate_request_http_ver(char *data_received, size_t data_length) { if (data_received == NULL) {
        return -1;
    }

    if (data_length == NULL) {
        return -1;
    }

};

static int validate_request_start_line(char *data_received, size_t data_length) {
    if (data_received == NULL) {
        return -1;
    }

    if (data_length == NULL) {
        return -1;
    }

    if (validate_request_method(data_received, data_length)) {
        return -1;
    }

    if (validate_request_path(data_received, data_length)) {
        return -1;
    }

    if (validate_request_http_ver(data_received, data_length)) {
        return -1;
    }

    return 0;
};

static int validate_request_header(char *data_received, size_t data_length) {
    if (data_received == NULL) {
        return -1;
    }

    if (data_length == NULL) {
        return -1;
    }
    



};

static int validate_request_line(char *data_received, size_t data_length) {

    if (data_received == NULL) {
        return -1;
    }

    if (data_length == NULL) {
        return -1;
    }

    char *start_line = strtok(data_received, "\r\n");
    start_line = strtok(start_line, " ");

    if (start_line == NULL) {
        return -1;
    }
    
    int request_line_index = 0; 

    while (start_line != NULL) {
        printf("start_line: %s\n", start_line);

        switch (request_line_index) {
            case 0:
                if (strncmp(start_line, "GET", 3)) {
                    break;
                }
                else if (strncmp(start_line, "POST", 4)) {
                    break;
                }
                else {
                    return -1;
                }
            case 1:
                size_t path_length = strlen(start_line); 
                if (validate_request_path(start_line, path_length)) {
                    return -1;
                }
                break;
            case 2:
                if (!strncmp(start_line, "HTTP/1.1", 8)) {
                    break;
                }
                else {
                    return -1;
                }
            default:
                return -1;
        }
        start_line = strtok(NULL, " ");

        request_line_index++;
    }
};

int validate_request(char *data_received, size_t data_length) {
    
    int err;
    if (data_received == NULL) {
        return -1;
    }

    if (data_length == NULL) {
        return -1;
    }
    
    err = validate_request_line(data_received, data_length);
    if (err) {
        return -1;
    }

};
