#ifndef PIECE_H
#define PIECE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>


class Board;

class Piece : public QGraphicsPixmapItem
{
private:

    QPointF offset, prev;
    qreal tempZ;
    Board *parentBoard;


public:
    Piece(QPixmap &pixmap, Board *nparent);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PIECE_H
