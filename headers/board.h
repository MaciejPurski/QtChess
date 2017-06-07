#ifndef BOARD_H
#define BOARD_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QVector>
#include <QPainter>
#include <utility>
#include "piece.h"
#include "clock.h"

/* GUI representation of the board. Communicates with the game engine using move method */
class Board : public QGraphicsView
{

    Q_OBJECT
public:
    enum Color {WHITE, BLACK};
    explicit Board(QWidget *parent = 0);

    //Method initializes both white and black pieces. if color=0 first player is white
    void initialize(Color color);
    void move(Piece *toMove, const QPointF &prev, const QPointF &next);

private:
    QGraphicsScene *scene;
    QVector<Piece*> white;
    QVector<Piece*> black;
    QPixmap picture;
    QPointF prev;

    std::pair<int,int> mapCoordinates(QPointF input);
    void newTurn();
    void loadPieces();
    void loadPiecesSet(Color color);
    void setPieces(Color color);
    void activatePieces(Color color);
    void deactivatePieces(Color color);
    void setGameFinished();

public slots:
    void setGameFinishedSlot();

};




#endif // BOARD_H
