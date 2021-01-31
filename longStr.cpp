//
// Created by Andrey on 28.12.2020.
//
#include "longStr.h"
#define BIT 8


char * ltoab(long num,char * c){
    for (int i = 0; i < (sizeof(num)*BIT); ++i){
       c[i] = static_cast<bool>(num & 1 << (sizeof(num) * BIT - i - 1)) ? '1' : '0';

    }
    return c;
}

