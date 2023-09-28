#include <stdlib.h>
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

    if (data_length == 0) { return -1;
    }
    
    char *request_line_ptr;
    char *method = strtok_r(request_line, " ", &request_line_ptr);
    
    if (method == NULL) {
        return -1;
    }
    http_req_method_t req_method = validate_method(method, strlen(method));

    if (req_method == NONE) {
        return -1;
    }
    else {
        http_req->request_method = req_method;
    }
    
    char *path = strtok_r(NULL, " ", &request_line_ptr);

    if (path == NULL) {
        return -1;
    }

    if (validate_path(path, strlen(path))) {
        return -1;
    }
    else {
        server_path_t *server_path = malloc(sizeof(server_path_t));

        server_path->path = path;
        server_path->path_length = strlen(path);

        http_req->server_path = *server_path;
    }

    char *http_version = strtok_r(NULL, " ", &request_line_ptr);

    if (http_version == NULL) {
        return -1;
    }

    if (validate_version(http_version, strlen(http_version))) {
        return -1;
    }
    else {
        http_req->http_version = HTTP_ONE_POINT_ONE;
    }

    return 0;
}

static int validate_headers(char *request_line, size_t data_length, http_req_t *http_req) {
    if (request_line == NULL) {
        return -1;
    } 

    if (data_length == 0) {
        return -1;
    }
    
    char *request_line_end = strstr(request_line, "\r\n"); 
    if (request_line_end == NULL) {
        return -1;
    }
    memset(request_line_end, '\0', 2);

}


// Should either return a reference to an http_req_t or an error
http_req_t * validate_request(char *data_received, size_t data_length) {
    
    int err;
    if (data_received == NULL) {
        return NULL;
    }

    if (data_length == 0) {
        return NULL;
    }
   
    char *request_header_end = strstr(data_received, "\r\n\r\n"); 
    if (request_header_end == NULL) {
        return NULL;
    }
    memset(request_header_end, '\0', 4);
    char *request_body = request_header_end + 4;
    
    http_req_t *http_req = malloc(sizeof(http_req_t)); 

    err = validate_request_line(data_received, data_length, http_req);
    if (err) {
        return NULL;
    }

    err = validate_headers(data_received, data_length, http_req);
    if (err) {
        return NULL;
    }

    err = validate_body(data_received, data_length, http_req);
    if (err) {
        return NULL;
    }
#endif
    
    return http_req;
};
