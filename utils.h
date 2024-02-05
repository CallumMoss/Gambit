// utils.h
#pragma once
#include <cstdint>

bool piece_is_at_square(uint64_t board, int square) {
    return (board & (1ULL << square)) != 0;
}

uint64_t square_to_bits(int square) {
    // 1ULL << square
    // modulo with 8, then remaining is the file letter
}