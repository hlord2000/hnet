#ifndef HTTP_REQ_H__
#define HTTP_REQ_H__

#include <hstr.h>
#include <http/server.h>

typedef enum {
    GET,
    POST,
    PUT,
    DELETE,
    NONE,
    INVALID,
} http_req_method_t;

typedef enum {
    HTTP_OK = 200,
    HTTP_BAD_REQUEST = 400,
    HTTP_NOT_FOUND = 404,
    HTTP_METHOD_NOT_ALLOWED = 405,
    HTTP_INTERNAL_SERVER_ERROR = 500,
} http_ret_code_t;

typedef struct {
    http_req_method_t method;

    server_path_t server_path;

    str_t **headers;

    str_t * body;
} http_req_t;

int validate_request(str_t * data_received, http_req_t * http_req);

#endif
