#include "board.h"
#include "game.h"


Board::Board (QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    picture.load("board.png");
    if(picture.isNull()==true)
        qDebug() << "Fail not loaded";



    scene->setSceneRect(0.0, 0.0, 640.0, 640.0);
    pieces.resize(32);

    this->setFixedSize(642, 642);
    this->setBackgroundBrush(QBrush(picture));
    this->setScene(scene);


}


void Board::loadPieces()
{
    QPixmap piecesPicture("icons.png");
    QPixmap croppedPiece;

    if(piecesPicture.isNull())
        qDebug() << "File not opened\n";


    //white pawns
    int index=0;

    for(int j=0; j<2; j++)
    {

    croppedPiece = piecesPicture.copy(0, j*80, 80, 80);

    for(int i=0; i<8; i++)
    {
        pieces[index++]=new Piece(croppedPiece, this);
    }

    croppedPiece = piecesPicture.copy(80, j*80, 80, 80);

    pieces[index++] = new Piece(croppedPiece, this);
    pieces[index++] = new Piece(croppedPiece, this);

    for(int i=0; i<4; i++)
    {
        croppedPiece = piecesPicture.copy(160 + 80*i, j*80, 80, 80);
        pieces[index++] = new Piece(croppedPiece, this);
    }

    croppedPiece = piecesPicture.copy(480, j*80, 80, 80);

    pieces[index++] = new Piece(croppedPiece, this);
    pieces[index++] = new Piece(croppedPiece, this);

    }

}

void Board::setPieces(bool color)
{
    // TODO: usuwanie starych obiektow, jezeli gra byla juz inicjalizowana
    //setting pawns

    //set pawns
    for(int i=0; i<8; i++)
    {
        scene->addItem(pieces[i+ (!color)*16]);
        scene->items().first()->setPos(i*80, 80);

        scene->addItem(pieces[i+ color*16]);
        scene->items().first()->setPos(i*80, 480);
    }

    for(int i=0; i<2; i++) // rooks
    {
        scene->addItem(pieces[14+i]);
        scene->items().first()->setPos(i*560, (!color)*560);

        scene->addItem(pieces[30+i]);
        scene->items().first()->setPos(i*560, color*560);
    }

    for(int i=0; i<2; i++) // laufers
    {
        scene->addItem(pieces[8+i]);
        scene->items().first()->setPos(160 + i*240, (!color)*560);

        scene->addItem(pieces[24+i]);
        scene->items().first()->setPos(160 + i*240, color*560);
    }

    for(int i=0; i<2; i++) // knigths
    {
        scene->addItem(pieces[13-i]);
        scene->items().first()->setPos(80 + i*400, (!color)*560);

        scene->addItem(pieces[29-i]);
        scene->items().first()->setPos(80 + i*400, color*560);
    }



        scene->addItem(pieces[10]);
        scene->items().first()->setPos(240 + color*80, (!color)*560);

        scene->addItem(pieces[11]);
        scene->items().first()->setPos(240 + (!color)*80, (!color)*560);

        scene->addItem(pieces[26]);
        scene->items().first()->setPos(240 + color*80, color*560);

        scene->addItem(pieces[27]);
        scene->items().first()->setPos(240 + (!color)*80, color*560);



}


void Board::initialize(bool color)
{
   if(!scene->items().isEmpty())
       scene->clear();

    loadPieces();

    setPieces(color);

    Game::gameState.initialize();
}

void Board::move(Piece *toMove, const QPointF &prev, const QPointF &next)
{
    if(prev==next)
        return;
    if(!Game::checkMove(mapCoordinates(prev), mapCoordinates(next)))
    {
        toMove->setPos(prev);
        return;
    }
    newTurn();
    if(!toMove->collidingItems().isEmpty())
        delete toMove->collidingItems().at(0);

}

void Board::newTurn()
{

if(Game::state==Game::WhiteMove)
    Game::state=Game::BlackMove;
else
    Game::state=Game::WhiteMove;

}


std::pair<int,int> Board::mapCoordinates(QPointF input)
{

    //if(Game::state==Game::WhiteMove)
        return std::make_pair((int)input.rx()/80, (int)(7-input.ry()/80));
    //else if (Game::state==Game::BlackMove)
      //  return std::make_pair((int)(7-input.rx()/80), (int)(7-input.ry()/80));

}
