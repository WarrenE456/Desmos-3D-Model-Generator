#pragma once

#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    uint8_t head[80];
    uint32_t n;
} Header;
#pragma pack(pop)
