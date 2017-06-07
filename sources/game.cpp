#include "game.h"
#include <iostream>
#include <QDebug>
Game::State Game::state=Game::NotInitialized;
Game::CheckState Game::checkState = Game::NotChecked;
ChessBoard Game::gameState;

bool Game::checkMove(const Move& src, const Move& dst)
{
    Bitboard from = mapToBitboard(src);
    Bitboard to = mapToBitboard(dst);

    // check if move is legal in terms of game rules
    if(!gameState.isValid(from, to))
        return false;

    gameState.saveMove(from, to);
    gameState.updateChecks();

    //move cannot lead to one's check
    if (state == WhiteMove && gameState.getCheckedWhite()) {
        gameState.saveMove(to,from);
        return false;
    }

    if (state == BlackMove && gameState.getCheckedBlack()) {
        gameState.saveMove(to,from);
        return false;
    }

    //change game state if it was mat
    if (gameState.getMatWhite()) {
        state = Finished;
        checkState = WhiteMat;
    }

    if (gameState.getMatBlack()) {
        state = Finished;
        checkState = BlackMat;
    }
    qDebug()<<"White Check: "<<gameState.getCheckedWhite() << "Black Check: " << gameState.getCheckedBlack();
    qDebug()<<"White Mat: "<<gameState.getMatWhite() << "Black Mat: " << gameState.getMatBlack();
    return true;

}

Game::Bitboard Game::mapToBitboard(const Move& input)
{
    Bitboard result=1;
    result = result <<(8*input.second + input.first);

    return result;
}
