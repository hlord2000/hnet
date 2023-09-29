#include <util.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

static int append_token(tokens_t *tokens, char *token) {
    if (tokens == NULL || token == NULL) {
        return -1;
    }

    tokens->tokens = reallocarray(tokens->tokens, tokens->num_tokens + 1, sizeof(char *)); 
    tokens->tokens[tokens->num_tokens] = token;
    tokens->num_tokens++;

    return 0;
}

static int remove_delimiter(char *delimiter, int delimiter_length) {
    if (delimiter == NULL || delimiter_length < 1) {
        return -1;
    }

    // Zero the delimiter in the string
    memset(delimiter, '\0', delimiter_length);

    return 0;
}

tokens_t str2tok(char *str, char *delim) {
    if (str == NULL || delim == NULL) {
        return (tokens_t) { .tokens = NULL, .num_tokens = 0 };
    }

    int err;

    int delim_length = strlen(delim);
    tokens_t tokens;
    memset(&tokens, 0, sizeof(tokens_t));
    
    char *tok = str;

    while (true) {
        char *next_delim = strstr(tok, delim);
        if (next_delim == NULL) {
            err = append_token(&tokens, tok);
            if (err != 0) {
                break;
            }
            return tokens;
        }
        err = remove_delimiter(next_delim, delim_length);
        if (err != 0) {
            break;
        }
        err = append_token(&tokens, tok);
        if (err != 0) {
            break;
        }
        tok = next_delim + delim_length;
    }
}
