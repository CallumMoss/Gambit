// Board.h

#pragma once

#include <string>
#include <cstdint>
#include <sstream>
#include <vector>
#include <cctype>
#include <iostream>


void PrintBB(uint64_t board, bool mirrored);

class Board {
	private:
		// https://tearth.dev/bitboard-viewer/ layout 1
		// A piece's position on a given square is 2^n, where n is the square number.
		// ULL means unsigned long long, which gives us a 64 bit unsigned integer
		uint64_t pawns, knights, bishops, rooks, queens, kings = 0ULL;
		uint64_t white_pieces, black_pieces = 0ULL;

		char turn; // w for white, b for black
		bool white_short_castling_rights, black_short_castling_rights = false;
		bool white_long_castling_rights, black_long_castling_rights = false;
		uint64_t en_passant_target_square = 0ULL;
		int half_move_clock; // number of half moves, to test for 50 move rule
		int full_move_counter; // how many moves have been played

		char engine_colour = 'w';

	public:
		uint64_t get_pawns();
		uint64_t get_knights();
		uint64_t get_bishops();
		uint64_t get_rooks();
		uint64_t get_queens();
		uint64_t get_kings();

		uint64_t get_white_pieces();
		uint64_t get_black_pieces();

		char get_turn();
		bool get_white_short_castling_rights();
		bool get_white_long_castling_rights();
		bool get_black_short_castling_rights();
		bool get_black_long_castling_rights();
		uint64_t get_en_passant_target_square();
		int get_half_move_clock();
		int get_full_move_counter();

		void update_bitboards_from_fen(const std::string&);

		bool piece_is_at_square(uint64_t, int);
		void print_board();

		std::vector<uint64_t> move_gen();
		std::vector<uint64_t> knight_move_gen(int);
};