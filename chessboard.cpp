#include "chessboard.h"
#include <QDebug>
#include <iostream>


ChessBoard::ChessBoard()
{

}

void ChessBoard::initialize()
{
    white.all=0x000000000000FFFF;

    white.pawns=0x000000000000FF00;
    white.knigths=0x0000000000000042;
    white.queen=0x0000000000000010;
    white.rooks=0x0000000000000081;
    white.bishops=0x0000000000000024;
    white.queen=0x0000000000000008;
    white.king=0x0000000000000010;




    black.all=0xFFFF000000000000;
    black.pawns=0x00FF000000000000;
    black.knigths=0x4200000000000000;
    black.rooks=0x8100000000000000;
    black.bishops=0x2400000000000000;
    black.queen=0x0800000000000000;
    black.king=0x1000000000000000;
    empty=0x0000FFFFFFFF0000;

    isCheckedBlack=false;
    isCheckedWhite=false;
    isMatBlack=false;
    isMatWhite=false;
}


bool ChessBoard::isValid(Bitboard src, Bitboard dst)
{

    BitboardsSet* temp=&black;

    if((src & white.all) !=0)
        temp=&white;



    if((src & temp->pawns) != 0)
        return ((moveGeneratorPawn(src, temp) & dst )!= 0);

    else if ((src & temp->knigths) != 0)
        return ((moveGeneratorKnight(src, temp) & dst) != 0);

    else if ((src & temp->king) != 0)
        return ((moveGeneratorKing(src, temp) & dst) != 0);

    else if ((src & temp->rooks) != 0)
        return ((moveGeneratorVandH(src, temp) & dst) != 0);

    else if ((src & temp->bishops) != 0)
        return ((moveGeneratorDiaganAntiDiag(src, temp) & dst) != 0);

    else if ((src & temp->queen) != 0)
        return ((moveGeneratorDiaganAntiDiag(src, temp) & dst) != 0 || (moveGeneratorVandH(src, temp) & dst) != 0);
    else
        return false;

}

ChessBoard::Bitboard ChessBoard::moveGeneratorPawn(Bitboard board, BitboardsSet* set)
{
    Bitboard result=0;

    if(set==&white)
    {
         result=(board<<9) & black.all & (~RankMask[7]) & (~FileMask[0]); // capture right
         result=result | ( (board << 7) & black.all & (~RankMask[7]) & (~FileMask[7]) );  // capture left

         result=result | ((board << 8) & empty & (~RankMask[7])); // move one forward
         result=result | ((board << 16) & empty & (empty<<8) & RankMask[3]); //move two forward
    }
    else
    {
        result=(board>>9) & white.all & (~RankMask[0]) & (~FileMask[7]); // capture left
        result=result | ( (board >> 7) & white.all & (~RankMask[0]) & (~FileMask[0]) );  // capture right

        result=result | ((board >> 8) & empty & (~RankMask[0])); // move one forward
        result=result | ((board >> 16) & empty & (empty>>8) & RankMask[4]); //move two forward
    }

    return result;

    //TODO: promotion
}




ChessBoard::Bitboard ChessBoard::moveGeneratorKnight(Bitboard board, BitboardsSet* set)
{
    Bitboard result=0;

    result = ((board << 15) | (board>>17)) & (~set->all) & (~FileMask[7]); // one forward or backwards - left
    result = result | ( ((board << 6) | (board >> 10)) & (~set->all) & (~FileMask[6])); // two forwrads or backwards - left
    result = result | ( ((board << 17) | (board >> 15)) & (~set->all) & (~FileMask[0])); // one forwards or backwards - right
    result = result | ( ((board << 10) | (board >> 6)) & (~set->all) & (~FileMask[1])); // two forwards or backwards - right

    return result;
}



void ChessBoard::saveMove(Bitboard src, Bitboard dst)
{
    BitboardsSet* set=&black;
    BitboardsSet* other=&white;

    if((src & white.all) !=0)
    {
        set=&white;
        other=&black;
    }

    Bitboard* temp;
    if ((src & set->pawns) != 0)
        temp = &set->pawns;
    else if ((src & set->knigths) != 0)
        temp = &set->knigths;
    else if ((src & set->king) != 0)
        temp = &set->king;
    else if ((src & set->rooks) != 0)
        temp = &set->rooks;
    else if ((src & set->bishops) != 0)
        temp = &set->bishops;
    else if ((src & set->queen) != 0)
        temp = &set->queen;



    *temp = *temp & (~src);
    *temp = *temp | dst;

    set->all = set->all & (~src); // cancel previous position
    set->all = set->all | dst;   // save new position

    empty = empty | src;
    empty = empty & (~dst);

    if ((dst & other->all)!=0) // capture enemy's piece
    {
        other->all = other->all & (~dst);
        other->pawns = other->pawns & (~dst);
        other->bishops = other->bishops & (~dst);
        other->rooks = other->rooks & (~dst);
        other->knigths = other->knigths & (~dst);
        other->queen = other->queen & (~dst);
    }


}


ChessBoard::Bitboard ChessBoard::moveGeneratorKing(Bitboard board, BitboardsSet *set)
{
    Bitboard result=0;
    result = ((board >>8) | (board << 8)) & ~(set->all); // forwards and backwards
    result = result | (((board >> 1) | (board >> 9) | (board <<7) ) & ~(set->all) & ~(FileMask[7])); // left
    result = result | (((board << 1) | (board << 9) | (board >>7) ) & ~(set->all) & ~(FileMask[0])); // right

    return result;

}

ChessBoard::Bitboard ChessBoard::moveGeneratorVandH(Bitboard board, BitboardsSet *set)
{

    Bitboard occupied=~empty;
    Bitboard reverseOccupied=reverse(occupied);
    Bitboard reverseBoard=reverse(board);
    int number = mapToNumber(board); //field's position number
    Bitboard currentFile=FileMask[number % 8];
    Bitboard currentRank=RankMask[number /8];



    Bitboard horizontal=(occupied - 2*board) ^ reverse(reverseOccupied - 2*reverseBoard);

    Bitboard vertical = ( (occupied & currentFile) - (2 * board)) ^ reverse( reverse(occupied & currentFile) - (2 * reverseBoard));

    return (( horizontal & currentRank ) | (vertical & currentFile) ) & ~set->all;
}

ChessBoard::Bitboard ChessBoard::moveGeneratorEast (Bitboard board, BitboardsSet *set){
    Bitboard occupied=~empty;
    int number = mapToNumber(board);

    Bitboard result = occupied & RankMask[number / 8];
    result -= 2*board;
    result^=occupied;
    return result & RankMask[number/8] & ~set->all;
}

ChessBoard::Bitboard ChessBoard::moveGeneratorWest(Bitboard board, BitboardsSet *set) {
    Bitboard occupied=~empty;
    int number = mapToNumber(board);

    Bitboard result = reverse(occupied & RankMask[number / 8]);
    result -= 2*reverse(board);
    result = reverse(result);
    result^=occupied;
    return result & RankMask[number/8] & ~set->all;
}

ChessBoard::Bitboard ChessBoard::moveGeneratorNorth (Bitboard board, BitboardsSet *set) {
    Bitboard occupied=~empty;
    int number = mapToNumber(board);

    Bitboard result = occupied & FileMask[number % 8];
    result -= 2*board;
    result^=occupied;
    result = result & FileMask[number % 8] & ~set->all;

    return result;
}

ChessBoard::Bitboard ChessBoard::moveGeneratorSouth (Bitboard board, BitboardsSet *set) {
    Bitboard occupied=~empty;
    int number = mapToNumber(board);

    Bitboard result = reverse(occupied & FileMask[number % 8]);
    result -= 2*reverse(board);
    result = reverse(result);
    result^=occupied;
    return result & FileMask[number%8] & ~set->all;
}


ChessBoard::Bitboard ChessBoard::moveGeneratorDiaganAntiDiag(Bitboard board, BitboardsSet *set)
{
    Bitboard occupied=~empty;
    Bitboard reverseOccupied=reverse(occupied);
    Bitboard reverseBoard=reverse(board);

    int number = mapToNumber(board);
    Bitboard currentDiagonal=DiagonalMask[(number / 8) + (number % 8)];
    Bitboard currentAntiDiagonal=AntiDiagonalMask[(number / 8) + 7 - (number % 8)];
    Bitboard occupiedDiag = occupied & currentDiagonal;
    Bitboard occupiedAntiDiag = occupied & currentAntiDiagonal;



    Bitboard diagonal = (occupiedDiag - (2 * board)) ^ reverse(reverse(occupiedDiag) - (2 * reverseBoard));
    Bitboard antiDiagonal = ((occupiedAntiDiag) - (2 * board)) ^ reverse(reverse (occupiedAntiDiag) - (2 * reverseBoard));
    return ((diagonal & currentDiagonal) | (antiDiagonal & currentAntiDiagonal) ) & ~set->all;
}

ChessBoard::Bitboard ChessBoard::moveGeneratorDiagPositive (Bitboard board, BitboardsSet *set)
{
    Bitboard occupied=~empty;

    int number = mapToNumber(board);
    Bitboard currentDiagonal=DiagonalMask[(number / 8) + (number % 8)];
    Bitboard result = occupied & currentDiagonal;
    result -= 2*board;
    result^=occupied;
    return result = result & currentDiagonal & ~set->all;
}

ChessBoard::Bitboard ChessBoard::moveGeneratorDiagNegative (Bitboard board, BitboardsSet *set)
{
    Bitboard occupied=~empty;
    Bitboard reverseBoard=reverse(board);

    int number = mapToNumber(board);
    Bitboard currentDiagonal=DiagonalMask[(number / 8) + (number % 8)];
    Bitboard result = reverse(occupied & currentDiagonal);
    result -= 2*reverse(board);
    result = reverse(result);
    result^=occupied;
    return result & currentDiagonal & ~set->all;
}

ChessBoard::Bitboard ChessBoard::moveGeneratorAntiDiagPositive (Bitboard board, BitboardsSet *set)
{
    Bitboard occupied=~empty;
    int number = mapToNumber(board);
    Bitboard currentAntiDiagonal=AntiDiagonalMask[(number / 8) + 7 - (number % 8)];
    Bitboard result = occupied & currentAntiDiagonal;
    result -= 2*board;
    result^=occupied;
    return result = result & currentAntiDiagonal & ~set->all;
}


ChessBoard::Bitboard ChessBoard::moveGeneratorAntiDiagNegative (Bitboard board, BitboardsSet *set) {
    Bitboard occupied=~empty;
    Bitboard reverseBoard=reverse(board);

    int number = mapToNumber(board);
    Bitboard currentAntiDiagonal=AntiDiagonalMask[(number / 8) + 7 - (number % 8)];
    Bitboard result = reverse(occupied & currentAntiDiagonal);
    result -= 2*reverse(board);
    result = reverse(result);
    result^=occupied;
    return result & currentAntiDiagonal & ~set->all;

}

ChessBoard::Bitboard ChessBoard::moveGeneratorAttackPawn(Bitboard board, BitboardsSet *set)
{
    Bitboard result=0;

    if(set==&white)
    {
         result=(board<<9) & black.all & (~RankMask[7]) & (~FileMask[0]); // capture right
         result=result | ( (board << 7) & black.all & (~RankMask[7]) & (~FileMask[7]) );  // capture left
    }
    else
    {
        result=(board>>9) & white.all & (~RankMask[0]) & (~FileMask[7]); // capture left
        result=result | ( (board >> 7) & white.all & (~RankMask[0]) & (~FileMask[0]) );  // capture right
    }

    return result;
}


ChessBoard::Bitboard ChessBoard::reverse(Bitboard n)
{

   static const Bitboard m0 = 0x5555555555555555;
   static const Bitboard m1 = 0x0300c0303030c303;
   static const Bitboard m2 = 0x00c0300c03f0003f;
   static const Bitboard m3 = 0x00000ffc00003fff;
      n = ((n>>1)&m0) | (n&m0)<<1;
      n = swapbits<Bitboard, m1, 4>(n);
      n = swapbits<Bitboard, m2, 8>(n);
      n = swapbits<uint64_t, m3, 20>(n);
      n = (n >> 34) | (n << 30);
      return n;
}

ChessBoard::Bitboard ChessBoard::checkLine(BitboardsSet *set){
    // if any of the enemy's attacking bitboards intersects with the king, it is checked
    BitboardsSet *enemy = &black;



    if(set==enemy)
        enemy = &white;

    Bitboard temp = enemy->pawns;
    Bitboard attackedFields = 0;

    Bitboard result=0;

    while (temp)
    {

        if  ((moveGeneratorAttackPawn(findLSB(temp), enemy) & set->king )!=0) //king is checked by a pawn
        {
          return findLSB(temp); // there is no way that a pawn can cause double-check, returning position of the pawn
        }
        temp = resetLSB(temp);
    }

    temp = enemy->knigths;

    while (temp)
    {

        if  ((moveGeneratorKnight(findLSB(temp), enemy) & set->king )!=0) //king is checked by a knigth
        {
           result|=findLSB(temp); // adding to result bitboard a position of the knight which checkes the king
           break; //there's no need for checking other knights
        }
        temp = resetLSB(temp);
    }

    temp = enemy->bishops;

    while (temp)
    {
        attackedFields = moveGeneratorDiagPositive(findLSB(temp), enemy);
        if( (attackedFields & set->king) != 0)
        {
            result|=findLSB(temp) | attackedFields;
            break; //there's no need for checking other bishops
        }

        attackedFields = moveGeneratorDiagNegative(findLSB(temp), enemy);
        if( (attackedFields & set->king) != 0)
        {
            result|=findLSB(temp) | attackedFields;
            break; //there's no need for checking other bishops
        }

        attackedFields = moveGeneratorAntiDiagNegative(findLSB(temp), enemy);
        if( (attackedFields & set->king) != 0)
        {
            result|=findLSB(temp) | attackedFields;
            break; //there's no need for checking other bishops
        }

        attackedFields = moveGeneratorAntiDiagPositive(findLSB(temp), enemy);
        if( (attackedFields & set->king) != 0)
        {
            result|=findLSB(temp) | attackedFields;
            break; //there's no need for checking other bishops
        }

        // TODO: checking queen and rooks

        temp = resetLSB(temp);
    }

   temp = enemy->rooks;

   while (temp)
   {
       attackedFields = moveGeneratorNorth(findLSB(temp), enemy);

       if( (attackedFields & set->king) != 0)
       {

           result|=findLSB(temp) | attackedFields;
           break; //there's no need for checking other bishops
       }

       attackedFields = moveGeneratorSouth(findLSB(temp), enemy);
       if( (attackedFields & set->king) != 0)
       {
           result|=findLSB(temp) | attackedFields;
           break; //there's no need for checking other bishops
       }

       attackedFields = moveGeneratorEast(findLSB(temp), enemy);
       if( (attackedFields & set->king) != 0)
       {
           result|=findLSB(temp) | attackedFields;
           break; //there's no need for checking other bishops
       }

       attackedFields = moveGeneratorWest(findLSB(temp), enemy);
       if( (attackedFields & set->king) != 0)
       {
           result|=findLSB(temp) | attackedFields;
           break; //there's no need for checking other bishops
       }



       // TODO: checking queen and rooks

       temp = resetLSB(temp);
   }
    temp = enemy->queen;

    while (temp!=0)
    {
        attackedFields = moveGeneratorNorth(findLSB(temp), enemy);
        if( (attackedFields & set->king) != 0)
        {
            result|=findLSB(temp) | attackedFields;
            break; //there's no need for checking other bishops
        }

        attackedFields = moveGeneratorSouth(findLSB(temp), enemy);
        if( (attackedFields & set->king) != 0)
        {
            result|=findLSB(temp) | attackedFields;
            break; //there's no need for checking other bishops
        }

        attackedFields = moveGeneratorEast(findLSB(temp), enemy);
        if( (attackedFields & set->king) != 0)
        {
            result|=findLSB(temp) | attackedFields;
            break; //there's no need for checking other bishops
        }

        attackedFields = moveGeneratorWest(findLSB(temp), enemy);
        if( (attackedFields & set->king) != 0)
        {
            result|=findLSB(temp) | attackedFields;
            break; //there's no need for checking other bishops
        }

        attackedFields = moveGeneratorDiagPositive(findLSB(temp), enemy);
        if( (attackedFields & set->king) != 0)
        {
            result|=findLSB(temp) | attackedFields;
            break; //there's no need for checking other bishops
        }

        attackedFields = moveGeneratorDiagNegative(findLSB(temp), enemy);
        if( (attackedFields & set->king) != 0)
        {
            result|=findLSB(temp) | attackedFields;
            break; //there's no need for checking other bishops
        }

        attackedFields = moveGeneratorAntiDiagNegative(findLSB(temp), enemy);
        if( (attackedFields & set->king) != 0)
        {
            result|=findLSB(temp) | attackedFields;
            break; //there's no need for checking other bishops
        }

        attackedFields = moveGeneratorAntiDiagPositive(findLSB(temp), enemy);
        if( (attackedFields & set->king) != 0)
        {
            result|=findLSB(temp) | attackedFields;
            break; //there's no need for checking other bishops
        }


        // TODO: checking queen and rooks

        temp = resetLSB(temp);
    }

    return result;

}


ChessBoard::Bitboard ChessBoard::getAttackedFields(BitboardsSet *set){
    BitboardsSet *enemy = &black;
    Bitboard result = 0;

    if(set==enemy)
        enemy = &white;

    result |= moveGeneratorPawn(set->pawns, set); //king is checked by a pawn
    result |= moveGeneratorKnight(set->knigths, set);//king is checked by a knight


    Bitboard temp = set->bishops;

    while (temp!=0)
    {
        result |= moveGeneratorDiaganAntiDiag(findLSB(temp), enemy);
        temp = resetLSB(temp);
    }

   temp = set->rooks;

    while (temp!=0)
    {
        result |= (moveGeneratorVandH(findLSB(temp), enemy));  //king is checked by a rook
        temp = resetLSB(temp);
    }

    temp = set->queen;

    while (temp!=0)
    {
        result |= moveGeneratorVandH(findLSB(temp), enemy) |  moveGeneratorDiaganAntiDiag(findLSB(temp), enemy);  //king is checked by a queen

        temp = resetLSB(temp);
    }

    return result;
 }

ChessBoard::Bitboard ChessBoard::findLSB(Bitboard n)
{
    return n & (-n);
}

ChessBoard::Bitboard ChessBoard::resetLSB(Bitboard n)
{
    return n & (n-1);
}

void ChessBoard::updateChecks()
{
    Bitboard attackedByEnemy = checkLine(&white);
    isMatWhite=false;
    isMatBlack=false;

    if(attackedByEnemy!=0)
    {
        attackedByEnemy^=white.king;
        isCheckedWhite=true; // TODO: sprawdzenie czy da sie uciec
        if((getAttackedFields(&white) & attackedByEnemy) == 0)
        {
            isMatWhite=true;
            return;
        }
        else
            isMatWhite=false;
    }

    attackedByEnemy = checkLine(&black);


    if(attackedByEnemy!=0)
    {
        attackedByEnemy^=black.king;
        qDebug()<<attackedByEnemy;
        isCheckedBlack=true; // TODO: sprawdzenie czy da sie uciec
        if((getAttackedFields(&black) & attackedByEnemy) == 0)
        {
            isMatBlack=true;
            return;
        }

    }
    else
        isCheckedBlack = false;


}


int ChessBoard::mapToNumber(Bitboard board)
{
    Bitboard temp=1;
    int number=0;
    while(temp!=board)
    {
        number++;
        temp = temp <<1;
    }

    return number;
}
