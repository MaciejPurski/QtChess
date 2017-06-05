#include "mainwindow.h"
#include "ui_mainwindow.h"

// test comment
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    delete ui->mainToolBar;

    this->setWindowTitle("Chess");
    this->setFixedSize(1000, 750);
    main =  new QHBoxLayout ();

    game= new QMenu;
    other = new QMenu;



    game->setTitle("Game");
    other->setTitle("Other");
    game->addAction("New Game", this, SLOT(startInitializer()));
    game->addAction("Save Game");
    game->addAction("Load Game");
    game->addSeparator();
    game->addAction("Quit", this, SLOT(acceptQuit()));


    other->addAction("Help");
    other->addAction("Credits");
    clock=new Clock(this);
    board=new Board(this);
    main->addWidget(board);
    main->addWidget(clock);


    ui->menuBar->addMenu(game);
    ui->menuBar->addMenu(other);
    ui->centralWidget->setLayout(main);




}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::acceptQuit()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Test", "Quit?",
                                    QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        QApplication::quit();
    } else {
        qDebug() << "Yes was *not* clicked";
    }
}

void MainWindow::startInitializer()
{
    qDebug() << "Game initializer...";
    GameStart initializer(clock, board, this);
    initializer.exec();
}

