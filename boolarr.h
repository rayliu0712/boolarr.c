#include <stdbool.h>
typedef unsigned char byte;

#define BOOLSTR(b) ((b) ? "true" : "false")

byte* barr_new(int len, bool b);

bool barr_get(const byte* barr, int i);

void barr_set(byte* barr, int i, bool b);

void barr_fill(byte* barr, int start, int end, bool b);

void barr_str(const byte* barr, int len, char* dest);

void barr_print(const byte* barr, int len);

bool barr_all(const byte* barr, int len);

bool barr_any(const byte* barr, int len);