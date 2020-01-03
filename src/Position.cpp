#include <iostream>
#include "Position.h"
#include "Bitboard.h"
#include "bitops.h"
#include "misc.h"
#include "movegen.h"

//generate the move from, to, piece, capture, promoted, ep, castling

void Position::init() {
    /*
     * Init Zobrist Hashing Key Arrays
     */
    for (int piece = PIECE_NONE; piece <= B_KING; piece++) {
        for (int sq = 0; sq < SQUARE_NUM; sq++) {
            pieceKeys[piece][sq] = random64BitInteger();
        }
    }

    sideKey = random64BitInteger();

    for (int i = 0; i < 16; i++) {
        castleKeys[i] = random64BitInteger();
    }
}

void Position::hashPiece(Piece piece, Square sq) {
    zobristHash ^= pieceKeys[piece][sq];
}

void Position::hashCastle() {
    zobristHash ^= castleKeys[castlePerms];
}

void Position::hashSide() {
    zobristHash ^= sideKey;
}

void Position::hashEnPass() {
    zobristHash ^= pieceKeys[PIECE_NONE][enPassSquare];
}

void Position::flipTurn() {
    int turnTemp = turn;
    turn = static_cast<Color>(turnTemp ^ 1);
}

void Position::resetPosition() {
    for (int i = 0; i < PIECE_TYPE_NB; i++) {
        byType[i] = 0ULL;
    }

    byColor[COLOR_WHITE] = 0ULL;
    byColor[COLOR_BLACK] = 0ULL;

    for (int i = 0; i < PIECE_NB; i++) {
        pieceCount[i] = 0;
    }

    zobristHash = 0ULL;
    turn = COLOR_WHITE;
    enPassSquare = SQ_NONE;
    fiftyMove = 0;
    searchPly = 0;
    castlePerms = 0;
}

bool Position::setFromFEN(std::string fen) {
    const char *fenPtr = fen.c_str();
    resetPosition();
    int row = RANK_8;
    int col = FILE_A;


    int square = 0;
    // Iterate Thru Last Row, Check If Still Stuff to Iterate Thru
    while ((row >= RANK_1) && *fenPtr) {
        // Defaults to 1 Piece
        Piece piece;
        int count = 1;
        switch (*fenPtr) {
            case 'p':
                piece = B_PAWN;
                break;
            case 'r':
                piece = B_ROOK;
                break;
            case 'n':
                piece = B_KNIGHT;
                break;
            case 'b':
                piece = B_BISHOP;
                break;
            case 'k':
                piece = B_KING;
                break;
            case 'q':
                piece = B_QUEEN;
                break;
            case 'P':
                piece = W_PAWN;
                break;
            case 'R':
                piece = W_ROOK;
                break;
            case 'N':
                piece = W_KNIGHT;
                break;
            case 'B':
                piece = W_BISHOP;
                break;
            case 'K':
                piece = W_KING;
                break;
            case 'Q':
                piece = W_QUEEN;
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                piece = PIECE_NONE;
                // http://cs.smu.ca/~porter/csc/ref/asciifull.gif
                count = *fenPtr - '0';
                break;

            case '/':
            case ' ':
                // Move Array Indexes
                row--;
                col = FILE_A;
                // Increment pointer
                fenPtr++;
                continue;
            default:
                std::cerr << "ERROR IN PARSING fenPtr" << std::endl;
                return false;
        }
        for (int i = 0; i < count; i++) {
            square = row * 8 + col;
            if (piece != PIECE_NONE) {
                board[square] = piece;
                byType[getTypeFromPiece(piece)] |= (1ULL << square);
                byColor[getColorFromPiece(piece)] |= (1ULL << square);
                pieceCount[piece]++;
            }
            col++;
        }
        fenPtr++;
    }

    // Pointer Should Now Be At Side To Move Letter
    // Look Ma! I'm Using a Ternary Operator!
    // http://www.cplusplus.com/articles/1AUq5Di1/
    turn = (*fenPtr == 'w') ? COLOR_WHITE : COLOR_BLACK;
    fenPtr += 2;

    // Pointer Should Now Be At Castling Perms
    for (int i = 0; i < 4; i++) {
        if (*fenPtr == ' ') {
            break;
        }
        switch (*fenPtr) {
            case 'K':
                castlePerms |= WHITE_K_K;
                break;
            case 'Q':
                castlePerms |= WHITE_K_Q;
                break;
            case 'k':
                castlePerms |= BLACK_K_K;
                break;
            case 'q':
                castlePerms |= BLACK_K_Q;
                break;
            default:
                break;
        }
        fenPtr++;
    }
    fenPtr++;

    if (*fenPtr != '-') {
        enPassSquare = ((fenPtr[0]) - 'a') * 8 + fenPtr[1] - '1';
    }
    generatePositionKey();

    return true;
}

uint64_t Position::generatePositionKey() {
    zobristHash = 0ULL;

    for (int sq = SQ_A1; sq < SQ_H8; sq++) {
        Piece piece = board[sq];

        if (piece != PIECE_NONE) {
            zobristHash ^= pieceKeys[piece][sq];
        }
    }

    if (turn == COLOR_WHITE) {
        zobristHash ^= sideKey;
    }

    if (enPassSquare != SQ_NONE) {
        zobristHash ^= pieceKeys[PIECE_NONE][enPassSquare];
    }

    zobristHash ^= castleKeys[castlePerms];

    return zobristHash;
}

void Position::printBoard() {
    printf("Game Board:\n");

    for (int rank = RANK_8; rank >= RANK_1; rank--) {
        printf("%d  ", rank + 1);
        for (int file = FILE_A; file <= FILE_H; file++) {
            int sq = makeSquare(static_cast<Rank>(rank), static_cast<File>(file));
            int piece = board[sq];
            printf("%3c", pieceToChar[piece]);
        }
        printf("\n");
    }

    printf("\n   ");
    for (int file = FILE_A; file <= FILE_H; file++) {
        printf("%3c", 'a' + file);
    }

    printf("\n");
    printf("side:%c\n", colorToChar[turn]);
    printf("enPas:%d\n", enPassSquare);
    printf("castle:%c%c%c%c\n",
           castlePerms & WHITE_K_K ? 'K' : '-',
           castlePerms & WHITE_K_Q ? 'Q' : '-',
           castlePerms & BLACK_K_K ? 'k' : '-',
           castlePerms & BLACK_K_Q ? 'q' : '-');
    printf("PosKey:%lX\n", zobristHash);

    /*
    printf("\nWhite Bitboard:\n");
    printBitboard(byColor[COLOR_WHITE]);

    printf("\nBlack Bitboard:\n");
    printBitboard(byColor[COLOR_BLACK]);
    */
}

/* move
 * 0000 0000 0000 0000 0000 0011 1111 -> From, 0x3F (6 Bits)
 * 0000 0000 0000 0000 1111 1100 0000 -> To, 0x3F << 6 (6 Bits)
 * 0000 0000 0000 1111 0000 0000 0000 -> Piece, 0xF << 12 (4 Bits)
 * 0000 0000 1111 0000 0000 0000 0000 -> Captured, 0xF << 16 (4 Bits)
 * 0000 1111 0000 0000 0000 0000 0000 -> Promoted, 0xF << 20 (4 Bits)
 * 0001 0000 0000 0000 0000 0000 0000 -> EP, 0x1000000 (1 << 25) (1 Bit)
 * 0010 0000 0000 0000 0000 0000 0000 -> Castling, 0x2000000 (1 << 26) (1 Bit)
 */

std::vector<Move> Position::generateAllMoves() {
    std::vector<Move> moves;

    if (turn == COLOR_WHITE) {
        generateWhitePawnMoves(moves);
        generateWhiteKnightMoves(moves);
        generateWhiteBishopMoves(moves);
        generateWhiteRookMoves(moves);
        generateWhiteQueenMoves(moves);
        generateWhiteKingMoves(moves);
    } else {
        generateBlackPawnMoves(moves);
        generateBlackKnightMoves(moves);
        generateBlackBishopMoves(moves);
        generateBlackRookMoves(moves);
        generateBlackQueenMoves(moves);
        generateBlackKingMoves(moves);
    }

    return moves;
}

static void
addMoves(std::vector<Move>& moves, int from, int to, int piece, int capture, int promotion, int enPass, int castling) {
    Move move;
    move.move = gen_move(from, to, piece, capture, promotion, enPass, castling);
    moves.push_back(move);
}

void Position::generateWhitePawnMoves(std::vector<Move>& moves) {
    Bitboard pieceBB = byColor[COLOR_WHITE] & byType[PAWN];
    Bitboard currentMoveBB;
    while (pieceBB) {
        int from = popBit(pieceBB);
        // Valid Single Moves: If There Is No Piece in front
        currentMoveBB = PAWN_SINGLE_MOVES[COLOR_WHITE][from] & ~(byColor[COLOR_WHITE] & byColor[COLOR_BLACK]);

        if (currentMoveBB && getRank(static_cast<Square>(from)) == RANK_2) {
            currentMoveBB |= PAWN_DOUBLE_MOVES[COLOR_WHITE][from] & ~(byColor[COLOR_WHITE] & byColor[COLOR_BLACK]);
        }
        currentMoveBB |= PAWN_ATTACKS[COLOR_WHITE][from] & byColor[COLOR_BLACK];

        while (currentMoveBB) {
            int to = popBit(currentMoveBB);
            int pieceCaptured = board[to];

            if (getRank(static_cast<Square>(to)) == RANK_8) {
                addMoves(moves, from, to, W_PAWN, pieceCaptured, W_KNIGHT, false, false);
                addMoves(moves, from, to, W_PAWN, pieceCaptured, W_BISHOP, false, false);
                addMoves(moves, from, to, W_PAWN, pieceCaptured, W_ROOK, false, false);
                addMoves(moves, from, to, W_PAWN, pieceCaptured, W_QUEEN, false, false);
            } else {
                addMoves(moves, from, to, W_PAWN, pieceCaptured, false, false, false);
            }

            clearBit(currentMoveBB, to);
        }

        if (enPassSquare != SQ_NONE) {
            if (PAWN_ATTACKS[COLOR_WHITE][from] & (1ULL << enPassSquare)) {
                addMoves(moves, from, enPassSquare, W_PAWN, B_PAWN, false, true, false);
            }
        }

        clearBit(pieceBB, from);
    }
}

void Position::generateBlackPawnMoves(std::vector<Move>& moves) {
    Bitboard pieceBB = byColor[COLOR_BLACK] & byType[PAWN];
    Bitboard currentMoveBB;
    while (pieceBB) {
        int from = popBit(pieceBB);
        // Valid Single Moves: If There Is No Piece in front
        currentMoveBB = PAWN_SINGLE_MOVES[COLOR_BLACK][from] & ~(byColor[COLOR_WHITE] & byColor[COLOR_BLACK]);

        if (currentMoveBB && getRank(static_cast<Square>(from)) == RANK_7) {
            currentMoveBB |= PAWN_DOUBLE_MOVES[COLOR_BLACK][from] & ~(byColor[COLOR_WHITE] & byColor[COLOR_BLACK]);
        }
        // Add Attacks
        currentMoveBB |= PAWN_ATTACKS[COLOR_BLACK][from] & byColor[COLOR_WHITE];

        while (currentMoveBB) {
            int to = popBit(currentMoveBB);
            int pieceCaptured = board[to];

            if (getRank(static_cast<Square>(to)) == RANK_1) {
                addMoves(moves, from, to, B_PAWN, pieceCaptured, B_KNIGHT, false, false);
                addMoves(moves, from, to, B_PAWN, pieceCaptured, B_BISHOP, false, false);
                addMoves(moves, from, to, B_PAWN, pieceCaptured, B_ROOK, false, false);
                addMoves(moves, from, to, B_PAWN, pieceCaptured, B_QUEEN, false, false);
            } else {
                addMoves(moves, from, to, B_PAWN, pieceCaptured, false, false, false);
            }

            clearBit(currentMoveBB, to);
        }

        if (enPassSquare != SQ_NONE) {
            if (PAWN_ATTACKS[COLOR_BLACK][from] & (1ULL << enPassSquare)) {
                addMoves(moves, from, enPassSquare, B_PAWN, W_PAWN, false, true, false);
            }
        }

        clearBit(pieceBB, from);
    }
}

void Position::generateWhiteKnightMoves(std::vector<Move>& moves) {
    Bitboard pieceBB = byColor[COLOR_WHITE] & byType[KNIGHT];

    while (pieceBB) {
        int from = popBit(pieceBB);

        Bitboard moveBB = knightMoves(byColor[COLOR_WHITE], static_cast<Square>(from));
        while (moveBB) {
            int to = popBit(moveBB);
            int capturePiece = board[to];
            addMoves(moves, from, to, W_KNIGHT, capturePiece, false, false, false);
            clearBit(moveBB, to);
        }

        clearBit(moveBB, from);
    }
}

void Position::generateBlackKnightMoves(std::vector<Move>& moves) {
    Bitboard pieceBB = byColor[COLOR_BLACK] & byType[KNIGHT];

    while (pieceBB) {
        int from = popBit(pieceBB);

        Bitboard moveBB = knightMoves(byColor[COLOR_BLACK], static_cast<Square>(from));
        while (moveBB) {
            int to = popBit(moveBB);
            int capturePiece = board[to];
            addMoves(moves, from, to, B_KNIGHT, capturePiece, false, false, false);
            clearBit(moveBB, to);
        }

        clearBit(moveBB, from);
    }
}

void Position::generateWhiteBishopMoves(std::vector<Move>& moves) {
    Bitboard pieceBB = byColor[COLOR_WHITE] & byType[BISHOP];

    while (pieceBB) {
        int from = popBit(pieceBB);

        Bitboard moveBB = bishopAttacks(byColor[COLOR_WHITE] | byColor[COLOR_BLACK], static_cast<Square>(from)) &
                          ~byColor[COLOR_WHITE];
        while (moveBB) {
            int to = popBit(moveBB);
            int capturePiece = board[to];
            addMoves(moves, from, to, W_BISHOP, capturePiece, false, false, false);
            clearBit(moveBB, to);
        }

        clearBit(moveBB, from);
    }
}

void Position::generateBlackBishopMoves(std::vector<Move>& moves) {
    Bitboard pieceBB = byColor[COLOR_BLACK] & byType[BISHOP];

    while (pieceBB) {
        int from = popBit(pieceBB);

        Bitboard moveBB = bishopAttacks(byColor[COLOR_WHITE] | byColor[COLOR_BLACK], static_cast<Square>(from)) &
                          ~byColor[COLOR_BLACK];
        while (moveBB) {
            int to = popBit(moveBB);
            int capturePiece = board[to];
            addMoves(moves, from, to, B_BISHOP, capturePiece, false, false, false);
            clearBit(moveBB, to);
        }

        clearBit(moveBB, from);
    }
}

void Position::generateWhiteRookMoves(std::vector<Move>& moves) {
    Bitboard pieceBB = byColor[COLOR_WHITE] & byType[ROOK];

    while (pieceBB) {
        int from = popBit(pieceBB);

        Bitboard moveBB = rookAttacks(byColor[COLOR_WHITE] | byColor[COLOR_BLACK], static_cast<Square>(from)) &
                          ~byColor[COLOR_WHITE];
        while (moveBB) {
            int to = popBit(moveBB);
            int capturePiece = board[to];
            addMoves(moves, from, to, W_BISHOP, capturePiece, false, false, false);
            clearBit(moveBB, to);
        }

        clearBit(moveBB, from);
    }
}

void Position::generateBlackRookMoves(std::vector<Move>& moves) {
    Bitboard pieceBB = byColor[COLOR_BLACK] & byType[ROOK];

    while (pieceBB) {
        int from = popBit(pieceBB);

        Bitboard moveBB = bishopAttacks(byColor[COLOR_WHITE] | byColor[COLOR_BLACK], static_cast<Square>(from)) &
                          ~byColor[COLOR_BLACK];
        while (moveBB) {
            int to = popBit(moveBB);
            int capturePiece = board[to];
            addMoves(moves, from, to, B_BISHOP, capturePiece, false, false, false);
            clearBit(moveBB, to);
        }

        clearBit(moveBB, from);
    }
}

void Position::generateWhiteQueenMoves(std::vector<Move>& moves) {
    Bitboard pieceBB = byColor[COLOR_WHITE] & byType[QUEEN];

    while (pieceBB) {
        int from = popBit(pieceBB);

        Bitboard moveBB = (rookAttacks(byColor[COLOR_WHITE] | byColor[COLOR_BLACK], static_cast<Square>(from)) |
                           bishopAttacks(byColor[COLOR_WHITE] | byColor[COLOR_BLACK], static_cast<Square>(from))) &
                          ~byColor[COLOR_WHITE];
        while (moveBB) {
            int to = popBit(moveBB);
            int capturePiece = board[to];
            addMoves(moves, from, to, W_QUEEN, capturePiece, false, false, false);
            clearBit(moveBB, to);
        }

        clearBit(moveBB, from);
    }
}

void Position::generateBlackQueenMoves(std::vector<Move>& moves) {
    Bitboard pieceBB = byColor[COLOR_BLACK] & byType[QUEEN];

    while (pieceBB) {
        int from = popBit(pieceBB);

        Bitboard moveBB = (rookAttacks(byColor[COLOR_WHITE] | byColor[COLOR_BLACK], static_cast<Square>(from)) |
                           bishopAttacks(byColor[COLOR_WHITE] | byColor[COLOR_BLACK], static_cast<Square>(from))) &
                          ~byColor[COLOR_BLACK];
        while (moveBB) {
            int to = popBit(moveBB);
            int capturePiece = board[to];
            addMoves(moves, from, to, B_QUEEN, capturePiece, false, false, false);
            clearBit(moveBB, to);
        }

        clearBit(moveBB, from);
    }
}

void Position::generateWhiteKingMoves(std::vector<Move>& moves) {
    Bitboard pieceBB = byColor[COLOR_WHITE] & byType[KING];

    // Assume 1 King on board
    int from = popBit(pieceBB);
    Bitboard moveBB = kingMoves(byColor[COLOR_WHITE], static_cast<Square>(from));
    while (moveBB) {
        int to = popBit(moveBB);
        int capturePiece = board[to];
        addMoves(moves, from, to, W_KING, capturePiece, false, false, false);
        clearBit(moveBB, to);
    }

    if ((castlePerms & WHITE_K_K) && !((byColor[COLOR_WHITE] | byColor[COLOR_BLACK]) & OO_MASK[COLOR_WHITE])) {
        if (!squareAttacked(OO_ATTACK_MASK[COLOR_WHITE], COLOR_BLACK)) {
            addMoves(moves, from, SQ_G1, W_KING, false, false, false, true);
        }
    }
    if ((castlePerms & WHITE_K_Q) && !((byColor[COLOR_WHITE] | byColor[COLOR_BLACK]) & OOO_MASK[COLOR_WHITE])) {
        if (!squareAttacked(OOO_ATTACK_MASK[COLOR_WHITE], COLOR_BLACK)) {
            addMoves(moves, from, SQ_C1, W_KING, false, false, false, true);
        }
    }
}

void Position::generateBlackKingMoves(std::vector<Move>& moves) {
    Bitboard pieceBB = byColor[COLOR_BLACK] & byType[KING];

    // Assume 1 King on board
    int from = popBit(pieceBB);
    Bitboard moveBB = kingMoves(byColor[COLOR_BLACK], static_cast<Square>(from));
    while (moveBB) {
        int to = popBit(moveBB);
        int capturePiece = board[to];
        addMoves(moves, from, to, B_KING, capturePiece, false, false, false);
        clearBit(moveBB, to);
    }

    if ((castlePerms & BLACK_K_K) && !((byColor[COLOR_WHITE] | byColor[COLOR_BLACK]) & OO_MASK[COLOR_BLACK])) {
        if (!squareAttacked(OO_ATTACK_MASK[COLOR_BLACK], COLOR_WHITE)) {
            addMoves(moves, from, SQ_G8, B_KING, false, false, false, true);
        }
    }
    if ((castlePerms & BLACK_K_Q) && !((byColor[COLOR_WHITE] | byColor[COLOR_BLACK]) & OOO_MASK[COLOR_BLACK])) {
        if (!squareAttacked(OOO_ATTACK_MASK[COLOR_BLACK], COLOR_WHITE)) {
            addMoves(moves, from, SQ_C8, B_KING, false, false, false, true);
        }
    }
}

bool Position::squareAttacked(Square square, Color color) {
    Bitboard occupancy = byColor[COLOR_WHITE] | byColor[COLOR_BLACK];

    Bitboard pawns = byColor[color] & byType[PAWN];
    if (PAWN_ATTACKS[color ^ 1][square] & pawns) return true;

    Bitboard knights = byColor[color] & byType[KNIGHT];
    if (knightMoves(occupancy, square) & knights) return true;

    Bitboard king = byColor[color] & byType[KING];
    if (kingMoves(occupancy, square) & king) return true;

    Bitboard bishopsQueens = (byColor[color] & byType[QUEEN])
                             | (byColor[color] & byType[BISHOP]);
    //printBitboard(bishopAttacks(occupancy, square));
    if (bishopAttacks(occupancy, square) & bishopsQueens) return true;

    Bitboard rooksQueens = (byColor[color] & byType[QUEEN])
                           | (byColor[color] & byType[ROOK]);
    return (rookAttacks(occupancy, square) & rooksQueens) != 0;
}

// Checks if ANY squares in bitmap are attacked
bool Position::squareAttacked(Bitboard bitmap, Color color) {
    Bitboard bitmapClone = bitmap;
    while (bitmapClone) {
        if (squareAttacked(static_cast<Square>(popBit(bitmapClone)), color)) {
            return true;
        }
    }

    return false;
}

void Position::clearPiece(Square square) {
    Piece piece = board[square];
    clearBit(byColor[getColorFromPiece(piece)], square);
    clearBit(byType[getTypeFromPiece(piece)], square);
    board[square] = PIECE_NONE;

    hashPiece(piece, square);
}

void Position::addPiece(Piece piece, Square square) {
    board[square] = piece;
    setBit(byColor[getColorFromPiece(piece)], square);
    setBit(byType[getTypeFromPiece(piece)], square);

    hashPiece(piece, square);
}

bool Position::makeMove(int move) {
    int fromSq = mv_from(move);
    int toSq = mv_to(move);
    int pieceMoved = mv_piece(move);
    int capture = mv_cap(move);
    int promotion = mv_prom(move);

    // Save state
    PrevBoard prev;
    prev.move = move;
    prev.castlePerms = castlePerms;
    prev.enPassSquare = enPassSquare;
    prev.fiftyMove = fiftyMove;
    prev.positionKey = zobristHash;
    prevBoards.push_back(prev);

    hashCastle();
    castlePerms &= castle_update[fromSq];
    castlePerms &= castle_update[toSq];
    hashCastle();

    if (enPassSquare != SQ_NONE) {
        hashEnPass();
    }

    enPassSquare = SQ_NONE;

    if (pieceMoved == W_PAWN) {
        fiftyMove = 0;

        if (getRank(static_cast<Square>(fromSq)) == 2 && getRank(static_cast<Square>(toSq)) == 4) {
            enPassSquare = toSq - 8;
        }
    } else if (pieceMoved == B_PAWN) {
        fiftyMove = 0;

        if (getRank(static_cast<Square>(fromSq)) == 7 && getRank(static_cast<Square>(toSq)) == 5) {
            enPassSquare = toSq + 8;
        }
    }

    if (mv_castle(move)) {
        if (turn == COLOR_BLACK) {
            if (toSq == SQ_C8) {
                clearPiece(SQ_A8);
                addPiece(B_ROOK, SQ_D8);
            } else {
                clearPiece(SQ_H8);
                addPiece(B_ROOK, SQ_F8);
            }
        } else {
            if (toSq == SQ_C1) {
                clearPiece(SQ_A1);
                addPiece(W_ROOK, SQ_D1);
            } else {
                clearPiece(SQ_H1);
                addPiece(W_ROOK, SQ_F1);
            }
        }
    } else if (mv_ep(move)) {
        if (turn == COLOR_BLACK) {
            clearPiece(static_cast<Square>(toSq + 8));
        } else {
            clearPiece(static_cast<Square>(toSq - 8));
        }
    } else if (capture) {
        fiftyMove = 0;
        clearPiece(static_cast<Square>(toSq));
    }

    // Perform Move
    clearPiece(static_cast<Square>(fromSq));
    if (promotion) {
        pieceMoved = promotion;
    }

    addPiece(static_cast<Piece>(pieceMoved), static_cast<Square>(toSq));

    flipTurn();
    hashSide();

    if (turn == COLOR_BLACK) {
        // Note that color is reversed immediately before, so if turn == black, initial turn == white
        if (squareAttacked(byColor[COLOR_WHITE] & byType[KING], COLOR_BLACK)) {
            return false;
        }
    } else {
        if (squareAttacked(byColor[COLOR_BLACK] & byType[KING], COLOR_WHITE)) {
            return false;
        }
    }

    return true;
}

void Position::unmakeMove() {
    PrevBoard prevBoard = prevBoards.back();
    prevBoards.pop_back();

    int move = prevBoard.move;
    int fromSq = mv_from(move);
    int toSq = mv_to(move);
    int pieceMoved = mv_piece(move);
    int capture = mv_cap(move);

    clearPiece(static_cast<Square>(toSq));
    addPiece(static_cast<Piece>(pieceMoved), static_cast<Square>(fromSq));

    if (mv_castle(move)) {
        // Unmaking white move
        if (turn == COLOR_BLACK) {
            if (toSq == SQ_C1) {
                clearPiece(SQ_D1);
                addPiece(W_ROOK, SQ_A1);
            } else {
                clearPiece(SQ_F1);
                addPiece(W_ROOK, SQ_H1);
            }
        } else {
            if (toSq == SQ_C8) {
                clearPiece(SQ_D8);
                addPiece(B_ROOK, SQ_A8);
            } else {
                clearPiece(SQ_F8);
                addPiece(B_ROOK, SQ_H8);
            }
        }
    } else if (mv_ep(move)) {
        if (turn == COLOR_BLACK) {
            addPiece(B_PAWN, static_cast<Square>(toSq - 8));
        } else {
            addPiece(W_PAWN, static_cast<Square>(toSq + 8));
        }
    } else if (capture) {
        addPiece(static_cast<Piece>(capture), static_cast<Square>(toSq));
    }

    castlePerms = prevBoard.castlePerms;
    enPassSquare = prevBoard.enPassSquare;
    fiftyMove = prevBoard.fiftyMove;
    zobristHash = prevBoard.positionKey;

    flipTurn();
}