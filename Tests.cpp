// Tests.cpp

#include "Tests.h"
#include "Board.h"

#include <cassert>
#include <iostream>
#include <bitset>

void run_fen_tests() {
	Board board = Board();
	// Testing from the start position
	board.Board::update_bitboards_from_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	assert(board.get_pawns() == 0b11111111000000000000000000000000000000001111111100000000ULL);
	assert(board.get_knights() == 0b100001000000000000000000000000000000000000000000000000001000010ULL);
	assert(board.get_bishops() == 0b10010000000000000000000000000000000000000000000000000000100100ULL);
	assert(board.get_rooks() == 0b1000000100000000000000000000000000000000000000000000000010000001ULL);
	assert(board.get_queens() == 0b100000000000000000000000000000000000000000000000000000001000ULL);
	assert(board.get_kings() == 0b1000000000000000000000000000000000000000000000000000000010000ULL);
	assert(board.get_white_pieces() == 0b1111111111111111ULL);
	assert(board.get_black_pieces() == 0b1111111111111111000000000000000000000000000000000000000000000000ULL);

	assert(board.get_turn() == 'w');
	assert(board.get_white_castling_rights() == true);
	assert(board.get_black_castling_rights() == true);
	assert(board.get_en_passant_target_square() == NULL);
	assert(board.get_half_move_clock() == 0);
	assert(board.get_full_move_counter() == 1);

}