// Tests.cpp

#include "Tests.h"
#include "Board.h"

#include <cassert>

void run_fen_tests() {
	Board board = Board();
	// Testing from the start position
	board.update_bitboards_from_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	// Hex for the binary representations. Same thing, just shorter
	assert(board.get_pawns() == 0xff00000000ff00ULL);
	assert(board.get_knights() == 0x4200000000000042);
	assert(board.get_bishops() == 0x2400000000000024ULL);
	assert(board.get_rooks() == 0x8100000000000081ULL);
	assert(board.get_queens() == 0x800000000000008ULL);
	assert(board.get_kings() == 0x1000000000000010ULL);
	assert(board.get_white_pieces() == 0xffffULL);
	assert(board.get_black_pieces() == 0xffff000000000000ULL);
	assert((board.get_pawns() & board.get_black_pieces()) == 0xff000000000000ULL);

	assert(board.get_turn() == 'w');
	assert(board.get_white_short_castling_rights() == true);
	assert(board.get_white_long_castling_rights() == true);
	assert(board.get_black_short_castling_rights() == true);
	assert(board.get_white_long_castling_rights() == true);
	assert(board.get_en_passant_target_square() == NULL);
	assert(board.get_half_move_clock() == 0);
	assert(board.get_full_move_counter() == 1);

	//board.print_board();

	// Testing a more complex position
	board.Board::update_bitboards_from_fen("r1b2rk1/p1p1qppp/2np1n2/Pp2p3/2B1P3/3PBN2/1PP2RPP/RN1Q2K1 w - b6 0 10");
	assert(board.get_pawns() == 0xe508131008c600);
	assert(board.get_knights() == 0x240000200002ULL);
	assert(board.get_bishops() == 0x400000004100000ULL);
	assert(board.get_rooks() == 0x2100000000002001ULL);
	assert(board.get_queens() == 0x10000000000008ULL);
	assert(board.get_kings() == 0x4000000000000040ULL);
	assert(board.get_white_pieces() == 0x11438e64bULL);
	assert(board.get_black_pieces() == 0x65f52c1200000000ULL);
	assert((board.get_pawns() & board.get_black_pieces()) == 0xe5081200000000ULL);
	
	assert(board.get_turn() == 'w');
	assert(board.get_white_short_castling_rights() == false);
	assert(board.get_white_long_castling_rights() == false);
	assert(board.get_black_short_castling_rights() == false);
	assert(board.get_white_long_castling_rights() == false);
	assert(board.get_en_passant_target_square() == 0x20000000000ULL);
	assert(board.get_half_move_clock() == 0);
	assert(board.get_full_move_counter() == 10);
	//board.print_board();






	// Testing knight moves
	board.update_bitboards_from_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	std::vector<uint64_t> arr = board.knight_move_gen(1);
	for (uint64_t i : arr) {
		board.set_knights(i);
		board.set_white_pieces(i);

		// must update by keeping previous bits. Maybe find bit location and original and swap values

		board.print_board();
	}

	// Checking if looks like expected:
	board.update_bitboards_from_fen("8/8/8/8/8/2N5/8/8 w - - 0 1");
	//board.print_board();

	board.update_bitboards_from_fen("8/8/8/8/8/N7/8/8 w - - 0 1");
	//board.print_board();
}