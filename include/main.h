#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct MThd {
    uint32_t magic;
    uint32_t size;
    uint16_t SMF;
    uint16_t tracks;
    uint16_t bpm;
};
struct MTrk {
    uint32_t magic;
    uint32_t size;
};