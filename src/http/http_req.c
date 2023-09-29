#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include <util.h>

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
    if (request_line == NULL || http_req == NULL) {
        return -1;
    } 

    if (data_length == 0) {
        return -1;
    }
    
    tokens_t request_line_tokens = str2tok(request_line, " ");
    if (request_line_tokens.num_tokens != 3) {
        return -1;
    }

    http_req->request_method = validate_method(request_line_tokens.tokens[0], strlen(request_line_tokens.tokens[0]));
    if (http_req->request_method == NONE) {
        return -1;
    }

    if (validate_path(request_line_tokens.tokens[1], strlen(request_line_tokens.tokens[1]))) {
        return -1;
    }
    http_req->server_path.path = request_line_tokens.tokens[1];
    http_req->server_path.path_length = strlen(request_line_tokens.tokens[1]);

    http_req->http_version = validate_version(request_line_tokens.tokens[2], strlen(request_line_tokens.tokens[2]));
    if (http_req->http_version == -1) {
        return -1;
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
   
    http_req_t *http_req = malloc(sizeof(http_req_t)); 
    
    tokens_t request_tokens = str2tok(data_received, "\r\n\r\n");

    char *header = request_tokens.tokens[0];
    
    tokens_t header_tokens = str2tok(header, "\r\n");

    err = validate_request_line(header_tokens.tokens[0], strlen(header_tokens.tokens[0]), http_req);
    if (err) {
        return NULL;
    }
    
    return http_req;
};
