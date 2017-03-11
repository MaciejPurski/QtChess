#include "game.h"
#include <iostream>
#include <QDebug>
Game::State Game::state=Game::NotInitialized;
ChessBoard Game::gameState;


bool Game::checkMove(const Move& src, const Move& dst)
{
    Bitboard from = mapToBitboard(src);
    Bitboard to = mapToBitboard(dst);

    if(!gameState.isValid(from, to))
        return false;


    gameState.saveMove(from, to);
    gameState.updateChecks();
    qDebug()<<"White Check: "<<gameState.isCheckedWhite << "Black Check: " << gameState.isCheckedBlack;
    qDebug()<<"White Mat: "<<gameState.isMatWhite << "Black Mat: " << gameState.isMatBlack;
    return true;

}

Game::Bitboard Game::mapToBitboard(const Move& input)
{
    Bitboard result=1;
    result = result <<(8*input.second + input.first);

    return result;
}
