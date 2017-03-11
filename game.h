#ifndef GAME_H
#define GAME_H
#include <utility>
#include"chessboard.h"

class Game
{
public:
    using Bitboard=unsigned long long;
    using Move=std::pair<int,int>;
    enum State{NotInitialized, WhiteMove, BlackMove, Finished};
    enum CheckState{NotChecked, WhiteChecked, BlackChecked, WhiteMat, BlackMat, Draw };


    static State state;
    static bool checkMove(const Move& src, const Move& dst);
    static CheckState checkState;
    static Bitboard mapToBitboard(const Move& input);
    static ChessBoard gameState;
private:

    Game();

};

#endif // GAME_H
