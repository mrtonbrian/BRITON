//
// Created by brianton on 10/23/19.
//
#include <cstdint>
#include "Bitboard.h"

#ifndef CHESS_ENGINE_CPP_MOVEGEN_H
#define CHESS_ENGINE_CPP_MOVEGEN_H
uint64_t lineAttacks(Bitboard occ, const SMasks *pMask);

uint64_t rookAttacks(Bitboard occ, Square sq);

uint64_t bishopAttacks(Bitboard occ, Square sq);

uint64_t knightMoves(Bitboard occ, Square sq);

uint64_t kingMoves(Bitboard occ, Square sq);

uint64_t queenMoves(Bitboard occ, Square sq);
#endif //CHESS_ENGINE_CPP_MOVEGEN_H
