#ifndef HTTP_REQ_H__
#define HTTP_REQ_H__

#include <http.h>
#include <server.h>

typedef enum {
    GET,
    POST,
} http_req_method_t;

typedef struct {
    http_req_method_t request_method;

    server_path_t server_path;

    http_version_t http_version;
} http_req_t;


#endif
