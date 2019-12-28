#include <iostream>
#include "Position.h"
#include "Bitboard.h"
#include "misc.h"

char pieceToChar[15] = {
        '-',
        'P',
        'N',
        'B',
        'R',
        'Q',
        'K',
        '\0',
        '\0',
        'p',
        'n',
        'b',
        'r',
        'q',
        'k'
};

char colorToChar[2] = {
        'W',
        'B'
};

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

bool Position::movePiece(Piece piece, Square from, Square to) {
    // Create Bitboard With Only From And To Square Bits
    Bitboard changeBB = (1ULL << from) | (1ULL << to);
    // XOR With Corresponding Bitboards (From Square Is Unset, To Square Is Set)
    byColor[getColorFromPiece(piece)] ^= changeBB;
    byType[getTypeFromPiece(piece)] ^= changeBB;
    board[from] = PIECE_NONE;
    board[to] = piece;

    return true;
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
    enPassSquare = PIECE_NONE;
    fiftyMove = 0;
    searchPly = 0;
    castlePerms = 0;
    hisPly = 0;
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

    printf("\nWhite Bitboard:\n");
    printBitboard(byColor[COLOR_WHITE]);

    printf("\nBlack Bitboard:\n");
    printBitboard(byColor[COLOR_BLACK]);
}
