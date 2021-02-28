//
// Created by Andrey on 28.12.2020.
//

#include <cctype>
#include <cerrno>
#include <climits>

#include "longStr.h"


#define BIT 8


char *ltoab(long num, char *c) {
    for (int i = 0; i < (sizeof(num) * BIT); ++i) {
        if ((num & 1 << (sizeof(num) * BIT - i - 1)) != 0) {
            c[i] = '1';
        } else {
            c[i] = '0';
        }

    }
    return c;
}

long strtolMine(const char *nptr, char **end, int base) {
    const char *s;
    unsigned long acc;
    char c;
    unsigned long cut;
    int neg, any, limCut;
    //Skip spaces catch leading +/- allowing 0/0x

    s = nptr;
    do {
        c = *s++;
    } while (isspace((unsigned char) c));
    if (c == '-') {
        neg = 1;
        c = *s++;
    } else {
        neg = 0;
        if (c == '+')
            c = *s++;
    }
    if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X') &&
        ((s[1] >= '0' && s[1] <= '9') || (s[1] >= 'A' && s[1] <= 'F') || (s[1] >= 'a' && s[1] <= 'f'))) {
        c = s[1];
        s += 2;
        base = 16;
    }
    if (base == 0)
        base = c == '0' ? 8 : 10;
    acc = any = 0;
    if (base < 2 || base > 36)
        goto noConv;
    cut = neg ? (unsigned long) -(LONG_MIN + LONG_MAX) + LONG_MAX
              : LONG_MAX;
    limCut = cut % base;
    cut /= base;
    for (;; c = *s++) {
        if (c >= '0' && c <= '9')
            c -= '0';
        else if (c >= 'A' && c <= 'F')
            c -= 'A' - 10;
        else if (c >= 'a' && c <= 'f')
            c -= 'a' - 10;
        else
            break;
        if (c >= base)
            break;
        if (any < 0 || acc > cut || (acc == cut && c > limCut))
            any = -1;
        else {
            any = 1;
            acc *= base;
            acc += c;
        }
    }

    if (any < 0) {
        acc = neg ? LONG_MIN : LONG_MAX;
        errno = ERANGE;
    } else if (!any) {
        noConv:
        errno = EINVAL;
    } else if (neg)
        acc = -acc;
    if (end != nullptr)
        *end = (char *) (any ? s - 1 : nptr);
    return acc;
}

