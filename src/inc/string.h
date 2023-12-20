#ifndef STRING_H__
#define STRING_H__

typedef struct {
  char *str;
  size_t len;
} string;

string *string_new(char *str, size_t len);
int string_free(string *s);
int string_clear(string *s);

typedef struct {
    string *str_arr;
    size_t len;
} string_array;

string_array *string_array_new(size_t len);
void string_array_free(string_array *sa);
void string_array_clear(string_array *sa);

void string_array_append(string_array *sa, string *s);

int string_tokenize(string *s, string *delim, string_array *tokens);

#endif
