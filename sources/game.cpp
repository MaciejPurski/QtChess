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
    if (state == WhiteMove && gameState.isCheckedWhite) {
        gameState.saveMove(to,from);
        return false;
    }

    if (state == BlackMove && gameState.isCheckedBlack) {
        gameState.saveMove(to,from);
        return false;
    }

    //change game state if it was mat
    if (gameState.isMatWhite) {
        state = Finished;
        checkState = WhiteMat;
    }

    if (gameState.isMatBlack) {
        state = Finished;
        checkState = BlackMat;
    }
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
