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
} __attribute__((scalar_storage_order ("big-endian")));
struct MTrk {
    uint32_t magic;
    uint32_t size;
} __attribute__((scalar_storage_order ("big-endian")));

void convert(FILE* infile, FILE* outfile);