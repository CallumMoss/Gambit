#include <array>
#include <string>

class Board {

	private:
		// https://tearth.dev/bitboard-viewer/ layout 1
		// A piece's position on a given square is 2^n, where n is the square number.
		// ULL means unsigned long long, which gives us a 64 bit unsigned integer
		uint64_t pawns = 0b11111111000000000000000000000000000000001111111100000000ULL;

	public:

		using String = std::string;

		uint64_t translate_fen(String fen) {
			// the values between each / represents each rank, starting from 8th rank.
			// Horizontally goes from A to F
			int file = 0;
			for (int rank = 8; rank > 0; rank--) {
				file = 0;
				while (fen[file] != '/') {
					switch (fen[file]) {
						case 'r':

					}
				}
			}
		}
};