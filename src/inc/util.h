#ifndef UTIL_H__
#define UTIL_H__

typedef struct {
    char **tokens;
    int num_tokens;
} tokens_t;

tokens_t str2tok(char *str, char *delim);

#endif
