#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include <http.h>
#include <http_req.h>

static http_req_method_t validate_method(char *method, size_t data_length) {

    http_req_method_t http_method = NONE;
    if (method == NULL) {
        return NONE;
    }

    if (data_length == 0) {
        return NONE;
    }

    if (strncmp(method, "GET", 3) == 0) {
        http_method = GET;
    } else if (strncmp(method, "POST", 4) == 0) {
        http_method = POST;
    } else if (strncmp(method, "PUT", 3) == 0) {
        http_method = PUT;
    } else if (strncmp(method, "DELETE", 6) == 0) {
        http_method = DELETE;
    } else {
        http_method = NONE;
    }
}

static int validate_path(char *path, size_t data_length) {
    if (path == NULL) {
        return -1;
    }

    if (data_length == 0) {
        return -1;
    }
    
    char * path_exclusions[] = {"..", "//", "#", "?"};
    
    for (int i = 0; i < 4; i++) {
        if (strstr(path, path_exclusions[i]) != NULL) {
            return -1;
        }
    }
    
    char path_str[512];
    strncpy(path_str, "./www", data_length);
    strncat(path_str, path, data_length);
    if (access(path_str, F_OK) == -1) {
        return -1;
    }
    return 0;
}

static int validate_version(char *http_version, size_t data_length) {
    if (http_version == NULL) {
        return -1;
    } 

    if (data_length == 0) {
        return -1;
    }
    
    if (strncmp(http_version, "HTTP/1.1", 8) != 0) {
        return -1;
    }
    return 0;
}

static int validate_request_line(char *request_line, size_t data_length, http_req_t *http_req) {
    if (request_line == NULL) {
        return -1;
    }

    if (data_length == 0) {
        return -1;
    }
    
    char *request_line_ptr;
    char *method = strtok_r(request_line, " ", &request_line_ptr);
    
    if (method == NULL) {
        return -1;
    }

    if (validate_method(method, strlen(method)) == NONE) {
        return -1;
    }
    
    char *path = strtok_r(NULL, " ", &request_line_ptr);

    if (path == NULL) {
        return -1;
    }

    if (validate_path(path, strlen(path))) {
        return -1;
    }

    char *http_version = strtok_r(NULL, " ", &request_line_ptr);

    if (http_version == NULL) {
        return -1;
    }

    if (validate_version(http_version, strlen(http_version))) {
        return -1;
    }

    return 0;
}

// Should either return a reference to an http_req_t or an error
http_req_t * validate_request(char *data_received, size_t data_length) {
    
    int err;
    if (data_received == NULL) {
        return HTTP_REQ_ERROR;
    }

    if (data_length == 0) {
        return HTTP_REQ_ERROR;
    }
   
    char *header_ptr;
    char *request_line = strtok_r(data_received, "\r\n\r\n", &header_ptr);
    
    http_req_t *http_req;

    err = validate_request_line(data_received, data_length, http_req);
    if (err) {
        return HTTP_REQ_ERROR;
    }
    return ;
};
