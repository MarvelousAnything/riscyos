#include <lib/string.h>

/**
 * memset - Fill a block of memory with a specific value
 * @dest: Pointer to the block of memory to fill
 * @value: The value to set
 * @len: Number of bytes to be set to the value
 *
 * Return: Pointer to the memory area dest
 */
void *memset(void *dest, int value, size_t len) {
  unsigned char *ptr = dest;
  while (len-- > 0) {
    *ptr++ = (unsigned char)value;
  }
  return dest;
}

/**
 * memcpy - Copy a block of memory from source to destination
 * @dest: Destination buffer
 * @src: Source buffer
 * @len: Number of bytes to copy
 *
 * Return: Pointer to dest
 */
void *memcpy(void *dest, const void *src, size_t len) {
  unsigned char *d = dest;
  const unsigned char *s = src;
  while (len-- > 0) {
    *d++ = *s++;
  }
  return dest;
}

/**
 * memmove - Move a block of memory, handling overlapping regions
 * @dest: Destination buffer
 * @src: Source buffer
 * @len: Number of bytes to move
 *
 * Return: Pointer to dest
 */
void *memmove(void *dest, const void *src, size_t len) {
  unsigned char *d = dest;
  const unsigned char *s = src;
  if (d == s || len == 0) {
    return dest;
  }
  if (d < s) {
    while (len-- > 0) {
      *d++ = *s++;
    }
  } else {
    d += len;
    s += len;
    while (len-- > 0) {
      *--d = *--s;
    }
  }
  return dest;
}

/**
 * memcmp - Compare two blocks of memory
 * @ptr1: Pointer to the first block
 * @ptr2: Pointer to the second block
 * @len: Number of bytes to compare
 *
 * Return: An integer less than, equal to, or greater than zero if the first n
 * bytes of ptr1 is found to be less than, equal to, or greater than the first n
 * bytes of ptr2.
 */
int memcmp(const void *ptr1, const void *ptr2, size_t len) {
  const unsigned char *a = ptr1;
  const unsigned char *b = ptr2;
  while (len-- > 0) {
    if (*a != *b) {
      return *a - *b;
    }
    a++;
    b++;
  }
  return 0;
}

/**
 * strlen - Calculate the length of a string
 * @str: Null-terminated string
 *
 * Return: Number of characters in the string, excluding the null terminator
 */
size_t strlen(const char *str) {
  const char *s = str;
  while (*s) {
    s++;
  }
  return s - str;
}

/**
 * strnlen - Calculate the length of a string, up to a maximum number of
 * characters
 * @str: Null-terminated string
 * @maxlen: Maximum number of characters to examine
 *
 * Return: Number of characters in the string, up to maxlen
 */
size_t strnlen(const char *str, size_t maxlen) {
  const char *s = str;
  while (maxlen-- > 0 && *s) {
    s++;
  }
  return s - str;
}

/**
 * strcpy - Copy a string
 * @dest: Destination buffer
 * @src: Source string
 *
 * Return: Pointer to dest
 */
char *strcpy(char *dest, const char *src) {
  char *d = dest;
  while ((*d++ = *src++))
    ;
  return dest;
}

/**
 * strncpy - Copy a string, up to a maximum number of characters
 * @dest: Destination buffer
 * @src: Source string
 * @len: Maximum number of characters to copy
 *
 * Return: Pointer to dest
 */
char *strncpy(char *dest, const char *src, size_t len) {
  char *d = dest;
  while (len-- > 0) {
    if (*src) {
      *d++ = *src++;
    } else {
      *d++ = '\0';
    }
  }
  return dest;
}

/**
 * strcat - Concatenate two strings
 * @dest: Destination buffer, must be large enough to hold the result
 * @src: Source string
 *
 * Return: Pointer to dest
 */
char *strcat(char *dest, const char *src) {
  char *d = dest;
  while (*d) {
    d++;
  }
  while ((*d++ = *src++))
    ;
  return dest;
}

/**
 * strncat - Concatenate two strings, up to a maximum number of characters from
 * src
 * @dest: Destination buffer, must be large enough to hold the result
 * @src: Source string
 * @len: Maximum number of characters to append from src
 *
 * Return: Pointer to dest
 */
char *strncat(char *dest, const char *src, size_t len) {
  char *d = dest;
  while (*d) {
    d++;
  }
  while (len-- > 0 && *src) {
    *d++ = *src++;
  }
  *d = '\0';
  return dest;
}

/**
 * strcmp - Compare two strings
 * @str1: First string
 * @str2: Second string
 *
 * Return: An integer less than, equal to, or greater than zero if str1 is found
 *         to be less than, equal to, or greater than str2.
 */
int strcmp(const char *str1, const char *str2) {
  while (*str1 && (*str1 == *str2)) {
    str1++;
    str2++;
  }
  return (unsigned char)*str1 - (unsigned char)*str2;
}

/**
 * strncmp - Compare two strings up to a maximum number of characters
 * @str1: First string
 * @str2: Second string
 * @len: Maximum number of characters to compare
 *
 * Return: An integer less than, equal to, or greater than zero if the first n
 * characters of str1 is found to be less than, equal to, or greater than the
 * first n characters of str2.
 */
int strncmp(const char *str1, const char *str2, size_t len) {
  while (len-- > 0) {
    if (*str1 != *str2) {
      return (unsigned char)*str1 - (unsigned char)*str2;
    }
    if (*str1 == '\0') {
      break;
    }
    str1++;
    str2++;
  }
  return 0;
}

/**
 * strchr - Locate the first occurrence of a character in a string
 * @str: String to search
 * @c: Character to find (converted to char)
 *
 * Return: Pointer to the first occurrence of c in str, or NULL if not found
 */
char *strchr(const char *str, int c) {
  char ch = c;
  while (*str) {
    if (*str == ch) {
      return (char *)str;
    }
    str++;
  }
  return (*str == ch) ? (char *)str : NULL;
}

/**
 * strrchr - Locate the last occurrence of a character in a string
 * @str: String to search
 * @c: Character to find (converted to char)
 *
 * Return: Pointer to the last occurrence of c in str, or NULL if not found
 */
char *strrchr(const char *str, int c) {
  char ch = c;
  const char *last = NULL;
  while (*str) {
    if (*str == ch) {
      last = str;
    }
    str++;
  }
  return (char *)(*str == ch ? str : last);
}

/**
 * strstr - Locate a substring
 * @haystack: String to search
 * @needle: Substring to find
 *
 * Return: Pointer to the beginning of the substring in haystack, or NULL if not
 * found
 */
char *strstr(const char *haystack, const char *needle) {
  if (!*needle) {
    return (char *)haystack;
  }
  for (; *haystack; haystack++) {
    if (*haystack == *needle) {
      const char *h = haystack;
      const char *n = needle;
      while (*h && *n && (*h == *n)) {
        h++;
        n++;
      }
      if (!*n) {
        return (char *)haystack;
      }
    }
  }
  return NULL;
}
