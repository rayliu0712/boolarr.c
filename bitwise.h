#define ROWDOWN(a) ((a) >> 3)

#define ROWUP(a) (((a) + 7) >> 3)

#define COL(a) ((a) & 7)  // a % 8

#define INDEX(a) ((a) << 3)

#define MASK(len, prefix) (0xFFU >> (8 - len) << prefix)