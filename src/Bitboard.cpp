#include "Bitboard.h"

void printBitboard(Bitboard b) {
    uint64_t shift = 1ULL;
    for (int r = RANK_8; r >= RANK_1; r--) {
        for (int c = FILE_A; c <= FILE_H; c++) {
            if ((shift << makeSquare(static_cast<Rank>(r), static_cast<File>(c))) & b) {
                std::cout << "X";
            } else {
                std::cout << "-";
            }
        }
        std::cout << std::endl;
    }
}