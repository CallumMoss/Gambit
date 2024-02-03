// Board.cpp

#include "Board.h"

#include <cctype>
#include <iostream>

// const means that the getters dont modify the values
uint64_t Board::get_pawns() { return pawns; }
uint64_t Board::get_knights() { return knights; }
uint64_t Board::get_bishops() { return bishops; }
uint64_t Board::get_rooks() { return rooks; }
uint64_t Board::get_queens() { return queens; }
uint64_t Board::get_kings() { return kings; }

uint64_t Board::get_white_pieces() { return white_pieces; }
uint64_t Board::get_black_pieces() { return black_pieces; }

char Board::get_turn() { return turn; }
bool Board::get_white_castling_rights() { return white_castling_rights; }
bool Board::get_black_castling_rights() { return black_castling_rights; }
uint64_t Board::get_en_passant_target_square() { return en_passant_target_square; }
int Board::get_half_move_clock() { return half_move_clock; }
int Board::get_full_move_counter() { return full_move_counter; }

void Board::update_bitboards_from_fen(const std::string& fen) { // reference to fen that must remain constant
    // can add and check for invalid fens in the future

    pawns = knights = bishops = rooks = queens = kings = white_pieces = black_pieces = 0ULL; // resets bitboards

    // Create a stringstream from the input string
    std::istringstream iss(fen);
    std::vector<std::string> words;
    // Parse the string based on space (' ')
    std::string word;
    while (std::getline(iss, word, ' ')) {
        words.push_back(word);
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
                if (word == "KQkq") { white_castling_rights = black_castling_rights = true; }
                else if (word == "KQ") { white_castling_rights = true; black_castling_rights = false; }
                else if (word == "kq") { white_castling_rights = false; black_castling_rights = true; }
                else { white_castling_rights, black_castling_rights = false; } // if == "-"
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

                en_passant_target_square = 1ULL << (word[1] - 1 * 8 + file);
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
