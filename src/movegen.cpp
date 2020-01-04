//
// Created by brianton on 12/27/19.
//

#include "movegen.h"
#include "bitops.h"
#include <cassert>

uint64_t lineAttacks(Bitboard occ, const SMasks *pMask) {
    uint64_t lower, upper, mMS1B, ls1b, odiff;
    lower = pMask->lower & occ;
    upper = pMask->upper & occ;
    mMS1B = -1ULL << bsr(lower | 1); // ms1b of lower (at least bit zero)
    ls1b = upper & -upper;
    odiff = 2 * ls1b + mMS1B; // x86 lea option due to add -ms1b
    return pMask->line & odiff; // (pMask->lower | pMask->upper) & odiff;
}


uint64_t rookAttacks(Bitboard occ, Square sq) {
    return lineAttacks(occ, masks[sq] + 0) | lineAttacks(occ, masks[sq] + 1);
}


uint64_t bishopAttacks(Bitboard occ, Square sq) {
    return lineAttacks(occ, masks[sq] + 2) | lineAttacks(occ, masks[sq] + 3);
}

uint64_t knightMoves(Bitboard occ, Square sq) {
    return KNIGHT_ATTACKS[sq] & ~occ;
}

uint64_t kingMoves(Bitboard occ, Square sq) {
    return KING_ATTACKS[sq] & ~occ;
}

uint64_t queenMoves(Bitboard occ, Square sq) {
    return rookAttacks(occ, sq) | bishopAttacks(occ, sq);
}
