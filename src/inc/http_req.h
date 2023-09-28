#ifndef HTTP_REQ_H__
#define HTTP_REQ_H__

#include <http.h>
#include <server.h>

typedef enum {
    GET,
    POST,
    PUT,
    DELETE,
    NONE,
} http_req_method_t;

typedef struct {
    http_req_method_t request_method;

    server_path_t server_path;

    http_version_t http_version;
    
    char **headers;

    char *body;
} http_req_t;

typedef enum {
    HTTP_OK = 200,
    HTTP_BAD_REQUEST = 400,
    HTTP_NOT_FOUND = 404,
    HTTP_METHOD_NOT_ALLOWED = 405,
    HTTP_INTERNAL_SERVER_ERROR = 500,
} http_ret_code_t;

http_req_t * validate_request(char *data_received, size_t data_length);

#endif
