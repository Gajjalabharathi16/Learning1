# Longest Non-Repeating Substring Methods in C

## 1. Brute Force Method

```c
#include <stdio.h>
#include <string.h>

int areDistinct(char *str, int start, int end) {
    int visited[256] = {0};
    for (int i = start; i <= end; i++) {
        if (visited[(unsigned char)str[i]])
            return 0;
        visited[(unsigned char)str[i]] = 1;
    }
    return 1;
}

int longestUniqueSubstrBrute(char *str) {
    int maxLength = 0;
    int len = strlen(str);
    int startIndex = 0;

    for (int i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
            if (areDistinct(str, i, j)) {
                int currentLength = j - i + 1;
                if (currentLength > maxLength) {
                    maxLength = currentLength;
                    startIndex = i;
                }
            }
        }
    }

    printf("Brute Force: Substring = ");
    for (int i = 0; i < maxLength; i++)
        putchar(str[startIndex + i]);
    printf("\nLength = %d\n", maxLength);

    return 0;
}

int main() {
    char str[] = "abcdabcdefabc";
    longestUniqueSubstrBrute(str);
    return 0;
}

```

## 2. Sliding Window Method

```c
#include <stdio.h>
#include <string.h>

int longestUniqueSubstrSliding(char *str) {
    int visited[256];
    for (int i = 0; i < 256; i++) visited[i] = -1;

    int maxLength = 0, start = 0;
    int len = strlen(str);
    int startIndex = 0;

    for (int i = 0; i < len; i++) {
        if (visited[(unsigned char)str[i]] >= start) {
            start = visited[(unsigned char)str[i]] + 1;
        }
        visited[(unsigned char)str[i]] = i;
        int currentLength = i - start + 1;
        if (currentLength > maxLength) {
            maxLength = currentLength;
            startIndex = start;
        }
    }

    printf("Sliding Window: Substring = ");
    for (int i = 0; i < maxLength; i++)
        putchar(str[startIndex + i]);
    printf("\nLength = %d\n", maxLength);

    return 0;
}

int main() {
    char str[] = "abcdabcdefabc";
    longestUniqueSubstrSliding(str);
    return 0;
}
```

## 3. Pointer-Based Sliding Window Method 

```c
#include <stdio.h>

void longest_unique_substring_pointer(char *str) {
    int visited[256] = {0};
    char *start = str, *end = str;
    char *max_start = str;
    int max_len = 0;

    while (*end) {
        if (!visited[(unsigned char)*end]) {
            visited[(unsigned char)*end] = 1;
            int window_len = end - start + 1;
            if (window_len > max_len) {
                max_len = window_len;
                max_start = start;
            }
            end++;
        } else {
            visited[(unsigned char)*start] = 0;
            start++;
        }
    }

    printf("Pointer Method: Substring = ");
    for (int i = 0; i < max_len; i++)
        putchar(*(max_start + i));
    printf("\nLength = %d\n", max_len);
}

int main() {
    char str[] = "abcdabcdefabc";
    longest_unique_substring_pointer(str);
    return 0;
}


```

## 4. Bit Masking

```c
#include <stdio.h>
#include <string.h>

void longest_bitmask(char *str) 
{
    int max_len = 0;
    int start_index = 0;
    int len = strlen(str);

    for (int i = 0; i < len; i++)
    {
        int mask = 0;
        for (int j = i; j < len; j++) 
        {
            int ch = str[j] - 'a';
            if (mask & (1 << ch)) break;
            mask |= (1 << ch);
            if ((j - i + 1) > max_len) 
            {
                max_len = j - i + 1;
                start_index = i;
            }
        }
    }

    printf("Longest Unique Substring (Bitmask): ");
    for (int i = 0; i < max_len; i++)
        putchar(str[start_index + i]);
    printf("\nLength: %d\n", max_len);
}
int main() {
    char str[] = "abcdabcdefabc";
   longest_bitmask(str);
    return 0;
}
```

