// Board.cpp

#include "Board.h"

uint64_t Board::get_pawns() { return pawns; }
uint64_t Board::get_knights() { return knights; }
uint64_t Board::get_bishops() { return bishops; }
uint64_t Board::get_rooks() { return rooks; }
uint64_t Board::get_queens() { return queens; }
uint64_t Board::get_kings() { return kings; }

uint64_t Board::get_white_pieces() { return white_pieces; }
uint64_t Board::get_black_pieces() { return black_pieces; }

void Board::set_pawns(uint64_t pawns) { this->pawns = pawns; }
void Board::set_knights(uint64_t knights) { this->knights = knights; }
void Board::set_bishops(uint64_t bishops) { this->bishops = bishops; }
void Board::set_rooks(uint64_t rooks) { this->rooks = rooks; }
void Board::set_queens(uint64_t queens) { this->queens = queens; }
void Board::set_kings(uint64_t kings) { this->queens = queens; }

void Board::set_white_pieces(uint64_t white_pieces) { this->white_pieces = white_pieces; }
void Board::set_black_pieces(uint64_t black_pieces) { this->black_pieces = black_pieces; }

char Board::get_turn() { return turn; }
bool Board::get_white_short_castling_rights() { return white_short_castling_rights; }
bool Board::get_white_long_castling_rights() { return white_long_castling_rights; }
bool Board::get_black_short_castling_rights() { return black_short_castling_rights; }
bool Board::get_black_long_castling_rights() { return black_long_castling_rights; }
uint64_t Board::get_en_passant_target_square() { return en_passant_target_square; }
int Board::get_half_move_clock() { return half_move_clock; }
int Board::get_full_move_counter() { return full_move_counter; }


bool Board::piece_is_at_square(uint64_t board, int square) {
    return (board & (1ULL << square)) != 0;
}

void Board::print_bit_string(uint64_t bit_string) {
    // Print the binary representation using std::bitset
    std::cout << "Binary representation: " << std::bitset<64>(bit_string) << std::endl;
}


void Board::update_bitboards_from_fen(const std::string& fen) { // reference to fen that must remain constant
    // can add and check for invalid fens in the future

    pawns = knights = bishops = rooks = queens = kings = white_pieces = black_pieces = 0ULL; // resets bitboards

    // Create a stringstream from the input string
    std::istringstream iss(fen);
    std::vector<std::string> words;
    // Parse the string based on space (' ')
    std::string word;
    while (std::getline(iss, word, ' ')) {
        words.push_back(word); // pushes word to the back
    }

    int rank = 7, file = 0;
    for (char c : words[0]) {

        if (c == '/') {
            // this splits each rank
            rank--;
            file = 0;
        }
        else if (isdigit(c)) {
            file += (c - '0'); // skips empty files of this amount
        }
        else {
            uint64_t square = 1ULL << (rank * 8 + file);
            // shifts 1 bit, to represent there is a piece on the square, across the bitboard's bitstring
            // For example, c4 in LERF is 26. So you want to push a 1 onto the 26th bit of the bitstring
            switch (c) {
                // Bit boards are all 0s, by using or, the 1 is added in.
                // Need to use or instead of equals as after the first pawn is detected,
                // square wont remember where the 1 was originally for the first pawn
                case 'P': pawns |= square; white_pieces |= square; break;
                case 'N': knights |= square; white_pieces |= square; break;
                case 'B': bishops |= square; white_pieces |= square; break;
                case 'R': rooks |= square; white_pieces |= square; break;
                case 'Q': queens |= square; white_pieces |= square; break;
                case 'K': kings |= square; white_pieces |= square; break;
                case 'p': pawns |= square; black_pieces |= square; break;
                case 'n': knights |= square; black_pieces |= square; break;
                case 'b': bishops |= square; black_pieces |= square; break;
                case 'r': rooks |= square; black_pieces |= square; break;
                case 'q': queens |= square; black_pieces |= square; break;
                case 'k': kings |= square; black_pieces |= square; break;
            }
            file++;
        }
    }

    char file_letter; // declared out of switch statement
    int file_number;

    for (int i = 1; i < 6; i++) {
        std::string word = words[i];
        switch (i) {
            case 1: // which colour to move
                turn = word[0];
                break;
            case 2: // which colours have castling rights
                for (char c : word) {
                    switch (c) {
                        case('-'):
                            white_short_castling_rights = white_long_castling_rights = black_short_castling_rights = black_long_castling_rights = false;
                            break;
                        case('K'):
                            white_short_castling_rights = true;
                            break;
                        case('Q'):
                            white_long_castling_rights = true;
                            break;
                        case('k'):
                            black_short_castling_rights = true;
                            break;
                        case('q'):
                            black_long_castling_rights = true;
                            break;
                    }

                }
                break;
            case 3: // which squares are being targetted with en passant
                file_letter = word[0];
                if (file_letter == '-') { en_passant_target_square = NULL; break; }
                else if (file_letter == 'a') { file_number = 0; }
                else if (file_letter == 'b') { file_number = 1; }
                else if (file_letter == 'c') { file_number = 2; }
                else if (file_letter == 'd') { file_number = 3; }
                else if (file_letter == 'e') { file_number = 4; }
                else if (file_letter == 'f') { file_number = 5; }
                else if (file_letter == 'g') { file_number = 6; }
                else { file_number = 7; } // if == 'h'

                en_passant_target_square = 1ULL << ((word[1] - 1) * 8 + file_number);
                break;
            case 4: // how many half moves have been played
                half_move_clock = std::stoi(word); // converts from string to int
                break;
            case 5: // how many moves have been played
                full_move_counter = std::stoi(word);
                break;
        }
    }
}

void Board::print_board() {
    // get the or of white and black pieces
    uint64_t white_pawns = pawns & white_pieces;
    uint64_t black_pawns = pawns & black_pieces;
    uint64_t white_knights = knights & white_pieces;
    uint64_t black_knights = knights & black_pieces;
    uint64_t white_bishops = bishops & white_pieces;
    uint64_t black_bishops = bishops & black_pieces;
    uint64_t white_rooks = rooks & white_pieces;
    uint64_t black_rooks = rooks & black_pieces;
    uint64_t white_queen = queens & white_pieces;
    uint64_t black_queen = queens & black_pieces;
    uint64_t white_king = kings & white_pieces;
    uint64_t black_king = kings & black_pieces;

    char board[64] = {};

    for (int i = 0; i < 64; i++) {
        //if(board[i].isUpper())
        if (piece_is_at_square(white_pawns, i)){
           board[i] = 'P';
        }
        else if (piece_is_at_square(white_knights, i)) {
            board[i] = 'N';
        }
        else if (piece_is_at_square(white_bishops, i)) {
            board[i] = 'B';
        }
        else if (piece_is_at_square(white_rooks, i)) {
            board[i] = 'R';
        }
        else if (piece_is_at_square(white_queen, i)) {
            board[i] = 'Q';
        }
        else if (piece_is_at_square(white_king, i)) {
            board[i] = 'K';
        }
        else if (piece_is_at_square(white_rooks, i)) {
            board[i] = 'R';
        }
        else if (piece_is_at_square(black_pawns, i)) {
            board[i] = 'p';
        }
        else if (piece_is_at_square(black_knights, i)) {
            board[i] = 'n';
        }
        else if (piece_is_at_square(black_bishops, i)) {
            board[i] = 'b';
        }
        else if (piece_is_at_square(black_rooks, i)) {
            board[i] = 'r';
        }
        else if (piece_is_at_square(black_queen, i)) {
            board[i] = 'q';
        }
        else if (piece_is_at_square(black_king, i)) {
            board[i] = 'k';
        }
        else {
            board[i] = ' ';
        }
    }

    // print board
    std::string rank = "";
    std::cout << "  -------------------------------" << std::endl;
    for (int j = 64; j > 0; j--) { // do i need new variables?
        if (j % 8 == 0 && j != 64) {
            std::cout << " | " + rank << (j/8) + 1 << std::endl << "  -------------------------------" << std::endl;
            rank = "";
        }
        rank = std::string(1, board[j - 1]) + " | " + rank; // - 1 used so i can use 64 instead of 63
    }
    std::cout << " | " + rank << 1 << std::endl << "  -------------------------------" << std::endl;
    std::cout << "   A   B   C   D   E   F   G   H  " << std::endl << std::endl;
}

// move gen: generate the bitboards for each possible moving position, store them in an array, then use alpha beta negamax

/*std::vector<std::vector<uint64_t>>Board::move_gen() {
    std::vector<std::vector<uint64_t>> moves = {{}};
    if (engine_colour == 'w') {
        uint64_t white_remaining_pieces = white_pieces;
        for (int i = 0; i < 64 && white_remaining_pieces != 0ULL; i++) { 
            if (piece_is_at_square(white_pieces, i)) {
                white_remaining_pieces = white_remaining_pieces & 0ULL << i; // after calculates, eliminates piece
                // do stuff
                if (piece_is_at_square(white_pieces & pawns, i)) {

                }
                else if (piece_is_at_square(white_pieces & knights, i)) {
                    moves.push_back(knight_move_gen(i));
                }
                else if (piece_is_at_square(white_pieces & bishops, i)) {

                }
                else if (piece_is_at_square(white_pieces & rooks, i)) {

                }
                else if (piece_is_at_square(white_pieces & queens, i)) {

                }
                else { // if king

                }
            }
        }
    }
    else {}
    //return knight_move_gen(i);
}*/

std::vector<uint64_t> Board::knight_move_gen(int square) {
    std::vector<uint64_t> knight_moves = {};
    uint64_t own_pieces = white_pieces;
    if (turn == 'b') {
        own_pieces = black_pieces;
    }

    if((square % 8 != 0) && (square % 8 != 1) && (square >= 8)) {// should be checking left two columns and bottom row
        if (!piece_is_at_square(own_pieces, square - 10)) { // if there isnt its own piece on the target square
            uint64_t move_left_down = ((1ULL) << (square - 10)); // if on square 26, moves left to 24, then down a rank by 8 to 16
            knight_moves.push_back(move_left_down);
        }
    }
    if ((square % 8 != 7) && (square % 8 != 6) && (square >= 8)) {
        if (!piece_is_at_square(own_pieces, square - 6)) { // if there isnt its own piece on the target square
            uint64_t move_right_down = ((1ULL) << (square - 6)); // -8 for down, + 2 for right
            knight_moves.push_back(move_right_down);
        }
    }
    if ((square % 8 != 0) && (square % 8 != 1) && (square < 56)) {
        if (!piece_is_at_square(own_pieces, square + 6)) { // if there isnt its own piece on the target square
            uint64_t move_left_up = ((1ULL) << (square + 6));
            knight_moves.push_back(move_left_up);
        }
    }
    if ((square % 8 != 7) && (square % 8 != 6) && (square < 56)) {
        if (!piece_is_at_square(own_pieces, square = 10)) { // if there isnt its own piece on the target square
            uint64_t move_right_up = ((1ULL) << (square + 10));
            knight_moves.push_back(move_right_up);
        }
    }

    if ((square % 8 != 0) && (square < 48)) {
        if (!piece_is_at_square(own_pieces, square + 15)) { // if there isnt its own piece on the target square
            uint64_t move_up_left = ((1ULL) << (square + 15));
            knight_moves.push_back(move_up_left);
        }
    }
    if ((square % 8 != 7) && (square < 48)) {
        if (!piece_is_at_square(own_pieces, square + 17)) { // if there isnt its own piece on the target square
            uint64_t move_up_right = ((1ULL) << (square + 17));
            knight_moves.push_back(move_up_right);
        }
    }
    if ((square % 8 != 0) && (square >= 16)) {
        if (!piece_is_at_square(own_pieces, square - 17)) { // if there isnt its own piece on the target square
            uint64_t move_down_left = ((1ULL) << (square - 17));
            knight_moves.push_back(move_down_left);
        }
    }
    if ((square % 8 != 7) && (square >= 8)) {
        if (!piece_is_at_square(own_pieces, square - 15)) { // if there isnt its own piece on the target square
            uint64_t move_down_right = ((1ULL) << (square - 15));
            knight_moves.push_back(move_down_right);
        }
    }

    return knight_moves;
}

void make_move() {
    return;
}
