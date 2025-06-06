#include "boolarr.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitwise.h"

static void setbit(u8* x, size_t start, size_t len, bool b) {
    u8 mask = MASK(len, start);
    *x = (*x & ~mask) | (-b & mask);
}

BoolArr* barr_new(size_t len, bool b) {
    BoolArr* barr = malloc(sizeof(BoolArr));

    size_t rows = ROWUP(len);
    barr->_arr = malloc(rows);
    memset(barr->_arr, -b, rows);

    barr->len = len;

    return barr;
}

void barr_xcopy(BoolArr* dest,
                const BoolArr* src,
                size_t prefix,
                size_t start,
                size_t len) {
    assert(start + len <= src->len && prefix + len <= dest->len);

    if (COL(prefix) || COL(start)) {
        for (size_t i = 0; i < len; i++) {
            barr_set(dest, prefix + i, barr_get(src, start + i));
        }
    } else {
        size_t end_row = ROWDOWN(len);
        size_t t = INDEX(end_row);
        memcpy(dest->_arr + ROWDOWN(prefix), src->_arr + ROWDOWN(start),
               end_row);

        size_t col = COL(len);
        for (size_t i = 0; i < col; i++)
            barr_set(dest, prefix + t + i, barr_get(src, start + t + i));
    }
}

void barr_copy(BoolArr* dest, const BoolArr* src) {
    barr_xcopy(dest, src, 0, 0, src->len);
}

BoolArr* barr_clone(const BoolArr* barr) {
    BoolArr* dest = barr_new(barr->len, false);
    barr_xcopy(dest, barr, 0, 0, barr->len);
    return dest;
}

bool barr_get(const BoolArr* barr, size_t i) {
    assert(i < barr->len);
    return (barr->_arr[ROWDOWN(i)] >> COL(i)) & 1;
}

void barr_set(BoolArr* barr, size_t i, bool b) {
    assert(i < barr->len);
    setbit(barr->_arr + ROWDOWN(i), COL(i), 1, b);
}

void barr_free(BoolArr* barr) {
    free(barr->_arr);
    free(barr);
}

void barr_fill(BoolArr* barr, size_t start, size_t end, bool b) {
    assert(end <= barr->len && start <= end);

    size_t start_row = ROWDOWN(start);
    size_t end_row = ROWDOWN(end);

    if (start_row == end_row) {
        setbit(barr->_arr + start_row, COL(start), end - start, b);
    } else {
        size_t l_row = ROWUP(start);
        size_t l = INDEX(l_row);
        setbit(barr->_arr + start_row, COL(start), l - start, b);

        size_t r = INDEX(end_row);
        setbit(barr->_arr + end_row, COL(r), end - r, b);

        memset(barr->_arr + l_row, -b, end_row - l_row);
    }
}

void barr_not(BoolArr* barr) {
    size_t rows = ROWUP(barr->len);
    for (size_t i = 0; i < rows; i++)
        barr->_arr[i] = ~barr->_arr[i];
}

void barr_dump(const BoolArr* barr) {
    size_t rows = ROWUP(barr->len);
    for (size_t i = 0; i < rows; i++)
        printf("%08b\n", barr->_arr[i]);
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