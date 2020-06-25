#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

struct MThd {
    uint32_t magic;
    uint32_t size;
    uint16_t SMF;
    uint16_t tracks;
    uint16_t bpm;
} __attribute__((packed, scalar_storage_order ("big-endian")));
struct MTrk {
    uint32_t magic;
    uint32_t size;
} __attribute__((packed, scalar_storage_order ("big-endian")));

void convert(FILE* infile, FILE* outfile);