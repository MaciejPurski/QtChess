#include "board.h"
#include "game.h"


Board::Board (QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    picture.load(":/resources/board.png");
    if(picture.isNull()==true)
        qDebug() << "Fail not loaded";

    scene->setSceneRect(0.0, 0.0, 640.0, 640.0);
    black.resize(16);
    white.resize(16);

    this->setFixedSize(642, 642);
    this->setBackgroundBrush(QBrush(picture));
    this->setScene(scene);
}


void Board::loadPieces()
{
    loadPiecesSet(WHITE);
    loadPiecesSet(BLACK);
}

void Board::loadPiecesSet(Color color)
{
    QPixmap piecesPicture;
    QPixmap croppedPiece;

    QVector<Piece*> *pieces;
    if (color == BLACK) {
        pieces = &black;
        piecesPicture.load(":/resources/icons_black.png");
    }
    else {
        pieces = &white;
        piecesPicture.load(":/resources/icons_white.png");
    }

    if(piecesPicture.isNull())
        qDebug() << "File not opened\n";


    int index=0;

    croppedPiece = piecesPicture.copy(0, 0, 80, 80);

    for(int i=0; i<8; i++)
    {
        (*pieces)[index++]=new Piece(croppedPiece, this);
    }

    croppedPiece = piecesPicture.copy(80, 0, 80, 80);

    (*pieces)[index++] = new Piece(croppedPiece, this);
    (*pieces)[index++] = new Piece(croppedPiece, this);

    for(int i=0; i<4; i++)
    {
        croppedPiece = piecesPicture.copy(160 + 80*i, 0, 80, 80);
        (*pieces)[index++] = new Piece(croppedPiece, this);
    }

    croppedPiece = piecesPicture.copy(480, 0, 80, 80);

    (*pieces)[index++] = new Piece(croppedPiece, this);
    (*pieces)[index++] = new Piece(croppedPiece, this);

}

void Board::setPieces(Color color)
{
     // pieces set that should be visible as a first player or second
    QVector<Piece*> *first = &white;
    QVector<Piece*> *second = &black;

    if (color == WHITE) {
        second = &white;
        first = &black;
    }


    //set pawns
    for(int i=0; i<8; i++)
    {
        scene->addItem((*first)[i]);
        scene->items().first()->setPos(i*80, 80);

        scene->addItem((*second)[i]);
        scene->items().first()->setPos(i*80, 480);
    }

    for(int i=0; i<2; i++) // rooks
    {
        scene->addItem((*first)[14+i]);
        scene->items().first()->setPos(i*560, 0);

        scene->addItem((*second)[14+i]);
        scene->items().first()->setPos(i*560, 560);
    }

    for(int i=0; i<2; i++) // bishops
    {
        scene->addItem((*first)[8+i]);
        scene->items().first()->setPos(160 + i*240, 0);

        scene->addItem((*second)[8+i]);
        scene->items().first()->setPos(160 + i*240, 560);
    }

    for(int i=0; i<2; i++) // knigths
    {
        scene->addItem((*first)[13-i]);
        scene->items().first()->setPos(80 + i*400, 0);

        scene->addItem((*second)[13-i]);
        scene->items().first()->setPos(80 + i*400, 560);
    }



        scene->addItem((*first)[10]);
        scene->items().first()->setPos(240, 0);

        scene->addItem((*first)[11]);
        scene->items().first()->setPos(320, 0);

        scene->addItem((*second)[10]);
        scene->items().first()->setPos(240, 560);

        scene->addItem((*second)[11]);
        scene->items().first()->setPos(320 , 560);

}


void Board::initialize(Color color)
{
   if(!scene->items().isEmpty())
       scene->clear();

    loadPieces();

    setPieces(color);
    //activate white pieces
    activatePieces(Color::WHITE);
    deactivatePieces(Color::BLACK);

    Game::gameState.initialize();
    Game::checkState = Game::NotChecked;
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

    if(Game::state == Game::Finished) {
        setGameFinished();
    }
    newTurn();
    if(!toMove->collidingItems().isEmpty()) {
        scene->removeItem(toMove->collidingItems().front());
    }

}

void Board::newTurn()
{

    if(Game::state==Game::WhiteMove) {
         Game::state=Game::BlackMove;
         activatePieces(BLACK);
         deactivatePieces(WHITE);
    }
    else {
        Game::state=Game::WhiteMove;
        activatePieces(WHITE);
        deactivatePieces(BLACK);
    }

}


std::pair<int,int> Board::mapCoordinates(QPointF input)
{
     return std::make_pair((int)input.rx()/80, (int)(7-input.ry()/80));
}

void Board::activatePieces(Color color)
{
    QVector<Piece*> *vec = &white;

    if (color == BLACK)
        vec = &black;

    for (auto it : (*vec))
         it->setEnabled(true);

}

void Board::deactivatePieces(Color color)
{
    QVector<Piece*> *vec = &white;

    if (color == BLACK)
        vec = &black;

    for (auto it : (*vec))
         it->setEnabled(false);

}

void Board::setGameFinished() {
    QGraphicsTextItem * io = new QGraphicsTextItem;
    io->setTextWidth(50);
    io->setPos(300,300);
    QString winner;
    if (Game::checkState == Game::WhiteMat)
        winner = "BLACK WON";
    else
        winner = "WHITE WON";
    io->setPlainText(winner);

    scene->addItem(io);

    deactivatePieces(WHITE);
    deactivatePieces(BLACK);
    // TODO komunikacja z zegarem
}


void Board::setGameFinishedSlot() {
    setGameFinished();
}

