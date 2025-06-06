#include <stdbool.h>
#include <stddef.h>

#define BOOLSTR(b) ((b) ? "true" : "false")

typedef unsigned char u8;

typedef struct {
    u8* _arr;
    size_t len;
} BoolArr;

BoolArr* barr_new(size_t len, bool b);

void barr_xcopy(BoolArr* dest,
                const BoolArr* src,
                size_t prefix,
                size_t start,
                size_t len);

void barr_copy(BoolArr* dest, const BoolArr* src);

BoolArr* barr_clone(const BoolArr* barr);

bool barr_get(const BoolArr* barr, size_t i);

void barr_set(BoolArr* barr, size_t i, bool b);

void barr_free(BoolArr* barr);

void barr_fill(BoolArr* barr, size_t start, size_t end, bool b);

void barr_not(BoolArr* barr);

void barr_dump(const BoolArr* barr);

bool barr_all(const BoolArr* barr);

bool barr_any(const BoolArr* barr);