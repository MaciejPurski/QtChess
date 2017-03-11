#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QLayout>
#include <QMessageBox>
#include <QDebug>
#include <QAction>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>


#include "gamestart.h"
#include "board.h"
#include "clock.h"

namespace Ui {
class MainWindow;
class GameStart;
class Board;
class Clock;
class Piece;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void acceptQuit();
    void startInitializer();

private:

    Ui::MainWindow *ui;
    QHBoxLayout *main;
    QMenu *game, *other;
    Board *board;
    Clock *clock;
};

#endif // MAINWINDOW_H
