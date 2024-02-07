// Main.cpp

#include "Tests.h"
#include "Board.h"

int main() {
    run_fen_tests();
    
    /*Board board = Board();
    board.update_bitboards_from_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::vector<std::vector<uint64_t>> moves = board.move_gen();
    uint64_t move = board.eval_move(moves);
    board.make_move(move);*/
    return 0;
}
