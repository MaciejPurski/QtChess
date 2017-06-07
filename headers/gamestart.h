#ifndef GAMESTART_H
#define GAMESTART_H


#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QToolBox>
#include <QDialog>
#include <QRadioButton>
#include <QLabel>
#include <QLineEdit>
#include "board.h"
#include "clock.h"

/* Dialog used to initialize the game */
class GameStart : public QDialog
{
    Q_OBJECT
public:
    explicit GameStart(Clock *nclock, Board *nboard, QWidget *parent = 0);
public slots:
    void initializeGame();
private:

    QPushButton *start, *cancel;
    QLabel   *color, *time;
    QRadioButton *white, *black;
    QLineEdit *timeSet;

    QHBoxLayout *layout1, *layout2;
    QVBoxLayout *mainLayout;

    Clock *clock;
    Board *board;


};

#endif // GAMESTART_H


