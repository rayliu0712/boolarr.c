#include "boolarr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS(i) (((i) + 7) / 8)

static void setbit(u8* row, size_t start, size_t end, bool b) {
    // [start, end)

    start %= 8;
    end %= 8;
    size_t len = end - start;
    u8 mask = ((1U << len) - 1) << start;

    *row = (*row & ~mask) | (b ? mask : 0);
}

BoolArr* barr_new(size_t len, bool b) {
    BoolArr* barr = malloc(sizeof(BoolArr));

    size_t rows = ROWS(len);  // ceil
    barr->_arr = malloc(rows);
    memset(barr->_arr, b, rows);

    barr->len = len;

    return barr;
}

bool barr_get(const BoolArr* barr, size_t i) {
    size_t row = i / 8;
    size_t col = i % 8;
    return (barr->_arr[row] >> col) & 1;
}

void barr_set(BoolArr* barr, size_t i, bool b) {
    size_t row = i / 8;
    setbit(barr->_arr + row, i, i + 1, b);
}

void barr_free(BoolArr* barr) {
    free(barr->_arr);
    free(barr);
}

void barr_fill(BoolArr* barr, size_t start, size_t end, bool b) {
    size_t start_row = start / 8;
    size_t end_row = end / 8;

    if (start_row == end_row) {
        setbit(barr->_arr + start_row, start, end, b);
    } else {
        size_t l_row = ROWS(start);
        size_t l = l_row * 8;
        setbit(barr->_arr + start_row, start, l, b);

        size_t r_row = end_row;
        size_t r = r_row * 8;
        setbit(barr->_arr + r_row, r, end, b);

        memset(barr->_arr + l_row, 0xFF, r_row - l_row);
    }
}

void barr_str(const BoolArr* barr, char* dest) {
    for (size_t i = 0; i < barr->len; i++)
        dest[i] = BITSTR(barr_get(barr, i));
    dest[barr->len] = '\0';
}

void barr_print(const BoolArr* barr) {
    char* buffer = malloc(barr->len + 1);
    barr_str(barr, buffer);
    puts(buffer);
    free(buffer);
}

bool barr_all(const BoolArr* barr) {
    for (size_t i = 0; i < barr->len; i++)
        if (!barr_get(barr, i))
            return false;
    return true;
}

bool barr_any(const BoolArr* barr) {
    for (size_t i = 0; i < barr->len; i++)
        if (barr_get(barr, i))
            return true;
    return false;
}