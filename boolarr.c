#include "boolarr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

byte* barr_new(int len, bool b) {
    int n = (len + 7) / 8;  // ceil
    byte* barr = malloc(n);
    memset(barr, b, n);
    return barr;
}

bool barr_get(const byte* barr, int i) {
    int row = i / 8;
    int col = i % 8;
    return (barr[row] >> col) & 1;
}

void barr_set(byte* barr, int i, bool b) {
    int row = i / 8;
    int col = i % 8;
    byte mask = 1 << col;
    barr[row] = (barr[row] & ~mask) | (b << col);  // 清空該位，填充該位
}

void barr_fill(byte* barr, int start, int end, bool b) {
    if (start / 8 == end / 8) {
        for (int i = start; i < end; i++) {
            barr_set(barr, i, b);
        }
    } else {
        int a_end = (start + 7) / 8 * 8;
        for (int i = start; i < a_end; i++)
            barr_set(barr, i, b);

        int b_start = end / 8 * 8;
        for (int i = b_start; i < end; i++)
            barr_set(barr, i, b);

        memset(barr + (start != a_end), b, (b_start - a_end) / 8);
    }
}

void barr_str(const byte* barr, int len, char* dest) {
    for (int i = 0; i < len; i++)
        dest[i] = barr_get(barr, i) ? '1' : '0';
    dest[len] = '\0';
}

void barr_print(const byte* barr, int len) {
    char* buffer = malloc(len + 1);
    barr_str(barr, len, buffer);
    printf("%s\n", buffer);
    free(buffer);
}

bool barr_all(const byte* barr, int len) {
    for (int i = 0; i < len; i++)
        if (!barr_get(barr, i))
            return false;
    return true;
}

bool barr_any(const byte* barr, int len) {
    for (int i = 0; i < len; i++)
        if (barr_get(barr, i))
            return true;
    return false;
}