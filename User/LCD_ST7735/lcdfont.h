#ifndef __LCDFONT_H
#define __LCDFONT_H

#include "lcd.h"
#include "lcd_init.h"

typedef struct {
    unsigned char Index[3];
    unsigned char Msk[24];
} typFNT_UTF_8_12;


typedef struct {
    unsigned char Index[3];
    unsigned char Msk[32];
} typFNT_UTF_8_16;


typedef struct {
    unsigned char Index[3];
    unsigned char Msk[72];
} typFNT_UTF_8_24;


typedef struct {
    unsigned char Index[3];
    unsigned char Msk[128];
} typFNT_UTF_8_32;

extern const unsigned char ascii_0806[][8];
extern const unsigned char ascii_1206[][12];
extern const unsigned char ascii_1608[][16];
extern const unsigned char ascii_2412[][48];
extern const unsigned char ascii_3216[][64];


extern const typFNT_UTF_8_12 tfont12[];
extern const u16 tfont12_size;
extern const typFNT_UTF_8_16 tfont16[];
extern const u16 tfont16_size;
extern const typFNT_UTF_8_24 tfont24[];
extern const u16 tfont24_size;
extern const typFNT_UTF_8_32 tfont32[];
extern const u16 tfont32_size;

#endif

