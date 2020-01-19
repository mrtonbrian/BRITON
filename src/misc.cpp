//
// Created by brianton on 12/20/19.
//

#include "misc.h"
#include <random>
#include <cassert>
#include <sstream>
#include <chrono>

uint64_t random64BitInteger() {
    std::random_device seed;
    std::default_random_engine generator(seed());
    std::uniform_int_distribution<uint64_t> distribution(0, 0xFFFFFFFFFFFFFFFF);

    return distribution(generator);
}

long getTimeMs() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

std::string printMove(int move) {
    std::ostringstream out;
    int fRank = getRank(static_cast<Square>(mv_from(move)));
    int fFile = getFile(static_cast<Square>(mv_from(move)));
    int tRank = getRank(static_cast<Square>(mv_to(move)));
    int tFile = getFile(static_cast<Square>(mv_to(move)));

    out << (char) ('a' + fFile) << (char) ('1' + fRank) << (char) ('a' + tFile) << (char) ('1' +  tRank);

    int promotionPiece = mv_prom(move);
    if (promotionPiece) {
        char pieceChar = 'q';
        if (getTypeFromPiece(static_cast<Piece>(promotionPiece)) == KNIGHT) {
            pieceChar = 'n';
        } else if (getTypeFromPiece(static_cast<Piece>(promotionPiece)) == ROOK) {
            pieceChar = 'r';
        } else if (getTypeFromPiece(static_cast<Piece>(promotionPiece)) == BISHOP) {
            pieceChar = 'b';
        } else if (getTypeFromPiece(static_cast<Piece>(promotionPiece)) != QUEEN) {
            assert(false);
        }

        out << pieceChar;
    }

    return out.str();
}