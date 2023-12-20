#include <string.h>

string *string_new(char *str, size_t len) { 
    if (len < 0) {
        return NULL;
    }
    else if (str == NULL) {
        return NULL;
    }

    string *s = malloc(sizeof(string));
    s->str = malloc(len);
    memcpy(s->str, str, len);
    s->len = len;
    return s;
}

int string_free(string *s) {
    if (s == NULL) {
        return -1;
    }
    free(s->str);
    free(s);
    return 0;
}

int string_clear(string *s) {
    if (s == NULL) {
        return -1;
    }
    memset(s->str, 0, s->len);
    return 0;
}

string_array *string_array_new(size_t len) {
    if (len < 0) {
        return NULL;
    }
    string_array *sa = malloc(sizeof(string_array));
    sa->len = len;
    return 0;
}

int string_array_free(string_array *sa) {
    int err;

    if (sa == NULL) {
        return -1;
    }
    for (int i = 0; i < sa->len; i++) {
        err = string_free(sa->str_arr[i]);
        if (err < 0) {
            return err;
        }
    }
    free(sa->str_arr);
    free(sa);
    return 0;
}

int string_array_clear(string_array *sa) {
    if (sa == NULL) {
        return -1;
    }
    for (int i = 0; i < sa->len; i++) {
        string_clear(sa->str_arr[i]);
    }
    return 0;
}

/*
typedef struct {
  char *str;
  size_t len;
} string;

typedef struct {
    string *str_arr;
    size_t len;
} string_array;
*/

int string_array_append(string_array *sa, string *s) {
    if (sa == NULL || s == NULL) {
        return -1;
    }
    // Extend the array
    string *str_tmp = sa->str;
    sa->str = reallocarray(sa->str, sa->len + 1, sizeof(string));
    if (sa->str == NULL) {
        sa->str = str_tmp;
        return -1;
    }
    sa->str[sa->len] = s;
    sa->len++;
    return 0;
}

int string_tokenize(string *s, string *delim, string_array *tokens) {
    if (s == NULL || delim == NULL || tokens == NULL) {
        return -1;
    }

    if (delim->len > s->len) {
        return -1;
    }

    char *token_begin = s->str;
    for (int i = 0; i < s->len; i++) {
        if (memcmp(token_begin, delim->str, delim->len) == 0) {
            string *token = string_new(token_begin, i - (token_begin - s->str));
            string_array_append(tokens, token);
        }
        token_begin++;
    }
    return 0;
}
