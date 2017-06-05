#include "piece.h"
#include "board.h"
#include <QDebug>



Piece::Piece(QPixmap &pixmap, Board *nparent) : QGraphicsPixmapItem(pixmap), parentBoard(nparent)
{
    setAcceptedMouseButtons(Qt::LeftButton);
}


void Piece::mousePressEvent(QGraphicsSceneMouseEvent * event)
 {
      offset = event->pos();
      tempZ = zValue();
      this->setZValue(33);
      prev=pos();
 }
void Piece::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF temp=event->pos() - offset;
    moveBy(temp.x(), temp.y());

}

void Piece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setZValue(tempZ);
    qreal tempX=0;
    qreal tempY=0;
    while (tempX < event->scenePos().x())
        tempX+=80;

    while (tempY < event->scenePos().y())
        tempY+=80;

    setPos(tempX-80, tempY-80);

    parentBoard->move(this, prev, pos());
}
