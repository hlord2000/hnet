#include <http/http_req.h>
#include <hstr.h>
#include <errno.h>

static str_t CRLF_HSTR = { .chars = "\r\n", .length = 2 };

static str_t CRLFCRLF_HSTR = { .chars = "\r\n\r\n", .length = 4 };

static str_t SPACE_HSTR = { .chars = " ", .length = 1 };

static str_t GET_HSTR = { .chars = "GET", .length = 3 };

static str_t POST_HSTR = { .chars = "POST", .length = 4 };

static str_t PUT_HSTR = { .chars = "PUT", .length = 3 };

static str_t DELETE_HSTR = { .chars = "DELETE", .length = 6 };

static int validate_request_end(str_t * data_received) {
    if (data_received == NULL) {
        return -EINVAL;
    }

    if (data_received->length < 4) {
        return -EINVAL;
    }
    
    if (memcmp(data_received->chars + data_received->length - CRLFCRLF_HSTR.length, CRLFCRLF_HSTR.chars, CRLFCRLF_HSTR.length) != 0) {
        return -EINVAL;
    }

    return 0;
}

static http_req_method_t get_request_method(str_t * request_line) {

    http_req_method_t ret = INVALID;

    if (request_tokens == NULL) {
        ret = INVALID;
    }
    
    if (hstr_compare(request_tokens->tokens[0], hstr("GET", strlen("GET"))) == 0) {
        ret = GET;
    } 

    if (hstr_compare(request_tokens->tokens[0], hstr("POST", strlen("POST"))) == 0) {
        ret = POST;
    } 

    if (hstr_compare(request_tokens->tokens[0], hstr("PUT", strlen("PUT"))) == 0) {
        ret = PUT;
    } 
    
    if (hstr_compare(request_tokens->tokens[0], hstr("DELETE", strlen("DELETE"))) == 0) {
        ret = DELETE;
    } 

    return ret;
}

int validate_request(str_t * data_received, http_req_t * http_req) {
    if (data_received == NULL) {
        return -EINVAL;
    }

    if (validate_request_end(data_received)) {
        return -EINVAL;
    }

    http_req_t * request = calloc(1, sizeof(http_req_t));
    if (request == NULL) {
        return -ENOMEM;
    }    
    
    str_tokens_t * header_lines = hstr_tokenize(data_received, &CRLF_HSTR);
    if (header_lines == NULL) {
        return -ENOMEM;
    }
    
    hstr_free(data_received); 

    if (header_lines->num_tokens < 1) {
        return -EINVAL;
    }

    str_tokens_t * request_tokens = hstr_tokenize(request_line, &SPACE_HSTR);
    
    http_req_method_t method = get_request_method(request_tokens[0]);
    if (method == INVALID) {
        return -EINVAL;
    }
    request->method = method;
    

    hstr_tokens_free(request_tokens); 
    http_req = request;

    return 0;
}

