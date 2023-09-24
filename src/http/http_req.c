#include <string.h>

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
    

};

static int validate_request_http_ver(char *data_received, size_t data_length) {
    if (data_received == NULL) {
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

int validate_request(char *data_received, size_t data_length) {
    int err;
    if (data_received == NULL) {
        return -1;
    }

    if (data_length == NULL) {
        return -1;
    }

    char header_delimiter[] = "\r\n\r\n";

    char *header_token;
    size_t header_length;

    header_token = strtok(data_received, line_delimiter);

    if (header_token == 0) {
        return -1;
    }
    
    header_length = strlen(header_token);

    err = validate_request_header(header_token, header_length);
    if (err) {
        return -1;
    }

};
