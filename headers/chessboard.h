#ifndef CHESSBOARD_H
#define CHESSBOARD_H


class ChessBoard
{
typedef unsigned long long Bitboard;
struct BitboardsSet {
    Bitboard all, pawns, bishops, knigths, rooks, queen, king;
};

public:
    ChessBoard();
    bool isValid(Bitboard src, Bitboard dst); // checks if the move is valid in terms of game rules
    void saveMove(Bitboard src, Bitboard dst); // saves move without checking its validility
    void updateChecks();

    bool isCheckedWhite, isCheckedBlack, isMatWhite, isMatBlack;


    void initialize();

private:
    BitboardsSet white, black;
    Bitboard empty;

    const Bitboard RankMask[8]={
        0xFF, 0xFF00, 0xFF0000, 0xFF000000, 0xFF00000000, 0xFF0000000000, 0xFF000000000000, 0xFF00000000000000
    };

    const Bitboard FileMask[8]={
        0x101010101010101, 0x202020202020202, 0x404040404040404, 0x808080808080808,
        0x1010101010101010, 0x2020202020202020, 0x4040404040404040, 0x8080808080808080
    };
    const Bitboard DiagonalMask[15]={
            0x1, 0x102, 0x10204, 0x1020408, 0x102040810, 0x10204081020, 0x1020408102040,
            0x102040810204080, 0x204081020408000, 0x408102040800000, 0x810204080000000,
            0x1020408000000000, 0x2040800000000000, 0x4080000000000000, 0x8000000000000000
    };
    const Bitboard AntiDiagonalMask[15]={
        0x80, 0x8040, 0x804020, 0x80402010, 0x8040201008, 0x804020100804, 0x80402010080402,
        0x8040201008040201, 0x4020100804020100, 0x2010080402010000, 0x1008040201000000,
        0x804020100000000, 0x402010000000000, 0x201000000000000, 0x100000000000000
    };



    Bitboard moveGeneratorPawn(Bitboard board, BitboardsSet *set);
    Bitboard moveGeneratorKnight(Bitboard board, BitboardsSet *set);
    Bitboard moveGeneratorKing(Bitboard board, BitboardsSet *set);
    Bitboard moveGeneratorVandH(Bitboard board, BitboardsSet *set);
    Bitboard moveGeneratorDiaganAntiDiag(Bitboard board, BitboardsSet *set);
    Bitboard moveGeneratorAttackPawn(Bitboard board, BitboardsSet *set);
    Bitboard moveGeneratorEast (Bitboard board, BitboardsSet *set);
    Bitboard moveGeneratorWest (Bitboard board, BitboardsSet *set);
    Bitboard moveGeneratorNorth (Bitboard board, BitboardsSet *set);
    Bitboard moveGeneratorSouth (Bitboard board, BitboardsSet *set);
    Bitboard moveGeneratorDiagPositive (Bitboard board, BitboardsSet *set);
    Bitboard moveGeneratorDiagNegative (Bitboard board, BitboardsSet *set);
    Bitboard moveGeneratorAntiDiagPositive (Bitboard board, BitboardsSet *set);
    Bitboard moveGeneratorAntiDiagNegative (Bitboard board, BitboardsSet *set);

    Bitboard getAttackedFields(BitboardsSet *set); // returns a bitboard of all attacked fields


    Bitboard checkLine(BitboardsSet *set); //return attacked line, if the king is checked, else returns 0



    Bitboard reverse (Bitboard arg);
    int mapToNumber(Bitboard board);
    Bitboard findLSB(Bitboard n);
    Bitboard resetLSB(Bitboard n);

    template <typename T, T m, int k>
    static inline T swapbits(T p) {
      T q = ((p>>k)^p)&m;
      return p^q^(q<<k);
    }



};

#endif //CHESSBOARD_H

