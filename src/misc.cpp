//
// Created by brianton on 12/20/19.
//

#include "misc.h"
#include <random>
#include <cassert>
#include <sstream>

#if defined _WIN32 || defined _WIN64
#include "windows.h"
#else
#include "sys/time.h"
#include "sys/select.h"
#endif

uint64_t random64BitInteger() {
    std::random_device seed;
    std::default_random_engine generator(seed());
    std::uniform_int_distribution<uint64_t> distribution(0, 0xFFFFFFFFFFFFFFFF);

    return distribution(generator);
}

int getTimeMs() {
#if defined _WIN32 || defined _WIN64
    return GetTickCount();
#else
    struct timeval t;
    gettimeofday(&t, 0);
    return t.tv_sec * 1000 + t.tv_usec / 1000;
#endif
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