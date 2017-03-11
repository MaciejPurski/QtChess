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

class Board : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);

    void initialize(bool color);
    void move(Piece *toMove, const QPointF &prev, const QPointF &next);

private:
    QGraphicsScene *scene;
    QVector<Piece*> pieces;
    QPixmap picture;
    QPointF prev;

    std::pair<int,int> mapCoordinates(QPointF input);
    void newTurn();
    void loadPieces();
    void setPieces(bool color);
   // void activatePieces(bool color);
    //void disactivatePieces(bool color);


};




#endif // BOARD_H
