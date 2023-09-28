#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <http_req.h>

char example_request[] = "GET /api/v1/users/1 HTTP/1.1\r\n" \
                        "Host: example.com\r\n" \
                        "Authorization: Bearer YOUR_ACCESS_TOKEN\r\n" \
                        "User-Agent: MyClient/1.0.0\r\n" \
                        "Accept: application/json\r\n";

int main(void) {
    int err;
    size_t data_length = sizeof(example_request);
    err = validate_request(example_request, data_length);
    printf("err: %d\n", err);
    return 0;
}
