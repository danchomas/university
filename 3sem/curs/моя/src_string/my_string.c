#include "my_string.h"

extern void *find_byte(const void *str, int symbol, size_t n) {
    unsigned char *ptr = (unsigned char *)str;
    void *out = NULL;
    size_t i = 0;

    while (i < n && out == NULL) {
        if (*ptr == (unsigned char)symbol) {
            out = ptr;
        } else {
            ++ptr;
            ++i;
        }
    }

    return out;
}

extern int compare_memory(const void *str1, const void *str2, size_t n) {
    const unsigned char *s1 = (const unsigned char *)str1;
    const unsigned char *s2 = (const unsigned char *)str2;
    int difference = 0;
    size_t i = 0;

    while (i < n && difference == 0) {
        difference = s1[i] - s2[i];
        ++i;
    }

    return difference;
}

extern void *fill_memory(void *str, int symbol, size_t n) {
    unsigned char *s = (unsigned char *)str;

    for (size_t i = 0; i < n; ++i) {
        s[i] = (unsigned char)symbol;
    }

    return str;
}

extern void *copy_memory(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    if (d < s || d >= s + n) {
        for (size_t i = 0; i < n; i++) d[i] = s[i];
    } else {
        for (size_t i = n; i > 0; i--) d[i - 1] = s[i - 1];
    }

    return dest;
}

extern char *concat_strings_limited(char *dest, const char *src, size_t n) {
    size_t dest_len = get_string_length(dest);
    size_t i = 0;

    for (; i < n && src[i]; ++i) {
        dest[dest_len + i] = src[i];
    }

    dest[dest_len + i] = '\0';

    return dest;
}

extern size_t get_string_length(const char *str) {
    const char *end = str;

    while (*end != '\0') end++;

    return end - str;
}

extern char *find_first_char(const char *str, int symbol) {
    while (*str != (char)symbol) {
        if (*str == '\0') return NULL;

        str++;

    }

    return (char *)str;
}

extern char *copy_string_limited(char *dest, const char *src, size_t n) {
    fill_memory(dest, '\0', n);

    for (size_t i = 0; i < n && src[i]; i++) {
        dest[i] = src[i];
    }

    return dest;
}

extern size_t count_not_matching_chars(const char *str1, const char *str2) {
    size_t counter = 0;

    for (const char *a = str1; *a; a++) {
      for (const char *b = str2; *b; b++) {
        if (*a == *b) return counter;
      }

      counter++;
    }

    return counter;
}

extern int compare_strings_limited(const char *str1, const char *str2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0') {
            return (unsigned char)str1[i] - (unsigned char)str2[i];
        }
    }
    return 0;
}

extern char *find_first_matching_char(const char *str1, const char *str2) {
    char *res = NULL;

    for (const char *a = str1; *a; ++a) {
        for (const char *b = str2; *b; ++b) {
            if (*a == *b) {
                res = (char *)a;
                return res;
            }
        }

        if (res) {
            return res;
        }
    }

    return res;
}

extern char *find_last_char(const char *str, int symbol) {
    char *res = NULL;
    size_t len = get_string_length(str);

    for (int i = len; i >= 0; --i) {
        if (str[i] == symbol) {
            res = ((char *)str) + i;
            return res;
        }
    }

    return res;
}

extern char *split_string(char *str, const char *delim) {
  static char *last;
  int c;

  if (str == NULL) str = last;

  do {
    if ((c = *str++) == '\0') return NULL;
  } while (find_first_char(delim, c));

  --str;

  last = str + count_not_matching_chars(str, delim);

  if (*last != '\0') *last++ = '\0';

  return str;
}

extern void *convert_to_uppercase(const char *str) {
  if (str == NULL) return NULL;

  char *new_str = (char *)calloc(get_string_length(str) + 1, sizeof(char));

  if (new_str == NULL) return NULL;

  for (size_t i = 0; i < get_string_length(str); i++) {
    if (str[i] < 'a' || str[i] > 'z') {
      new_str[i] = str[i];
    } else {
      new_str[i] = str[i] - ASCII_SHIFT;
    }
  }

  return (void *)new_str;
}

extern void *convert_to_lowercase(const char *str) {
  if (str == NULL) return NULL;

  char *new_str = (char *)calloc(get_string_length(str) + 1, sizeof(char));

  if (new_str == NULL) return NULL;

  for (size_t i = 0; i < get_string_length(str); i++) {
    if (str[i] < 'A' || str[i] > 'Z') {
      new_str[i] = str[i];
    } else {
      new_str[i] = str[i] + ASCII_SHIFT;
    }
  }

  return (void *)new_str;
}

extern void *insert_string(const char *src, const char *str, size_t start_index) {
  if (src == NULL || str == NULL) return NULL;

  size_t src_len = get_string_length(src);
  size_t str_len = get_string_length(str);

  if (start_index > src_len) return NULL;

  size_t new_len = src_len + str_len + 1;

  char *new_str = calloc(new_len, sizeof(char));

  if (new_str == NULL) return NULL;

  for (size_t i = 0; i < new_len; i++) {
    if (i < start_index) {
      new_str[i] = src[i];
    } else if (i < str_len + start_index) {
      new_str[i] = str[i - start_index];
    } else {
      new_str[i] = src[i - str_len];
    }
  }

  return (void *)new_str;
}

extern void *trim_string_edges(const char *src, const char *trim_chars) {
  if (src == NULL || trim_chars == NULL) return NULL;

  char *trimmed_str = NULL;
  size_t start = 0;
  size_t end = get_string_length(src) - 1;

  while (src[start] && find_first_char(trim_chars, src[start]) != NULL) {
    start++;
  }

  while (end > start && find_first_char(trim_chars, src[end])) {
    end--;
  }

  if (start <= end) {
    size_t trimmed_len = end - start + 2;

    trimmed_str = (char *)calloc(trimmed_len, sizeof(char));

    if (trimmed_str == NULL) return NULL;

    copy_string_limited(trimmed_str, src + start, end - start + 1);
  } else {
    trimmed_str = (char *)calloc(1, sizeof(char));

    if (trimmed_str == NULL) return NULL;
  }

  return trimmed_str;
}
