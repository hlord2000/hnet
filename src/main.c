#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <http_req.h>

char example_request[] = "GET /index.html HTTP/1.1\r\nHost: example.com\r\nAuthorization: Bearer YOUR_ACCESS_TOKEN\r\nUser-Agent: MyClient/1.0.0\r\nAccept: application/json\r\n\r\n<html><body><h1>Hello, World!</h1></body></html>";

int main(void) {
    http_req_t *req;
    req = validate_request(example_request, sizeof(example_request));
    if (req == NULL) {
        printf("Request is invalid\n");
        return -1;
    }

    return 0;
}
