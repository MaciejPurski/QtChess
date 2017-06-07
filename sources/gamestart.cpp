#include "gamestart.h"


GameStart::GameStart(Clock *nclock, Board *nboard, QWidget *parent) :
    clock(nclock), board(nboard), QDialog(parent)
{
    mainLayout = new QVBoxLayout(this);
    layout1 = new QHBoxLayout();
    layout2= new QHBoxLayout();
    this->setWindowTitle("New Game");

    white = new QRadioButton("White", this);
    white->setChecked(true);
    black = new QRadioButton ("Black", this);
    start = new QPushButton("Start", this);
    cancel = new QPushButton("Cancel", this);
    color = new QLabel ("Color", this);
    time = new QLabel("Time (in minutes)", this);
    timeSet = new QLineEdit("10", this);


    layout1->addWidget(white);
    layout1->addWidget(black);
    layout2->addWidget(start);
    layout2->addWidget(cancel);

    mainLayout->addWidget(color);

    mainLayout->addLayout(layout1);
    mainLayout->addWidget(time);
    mainLayout->addWidget(timeSet);
    mainLayout->addLayout(layout2);

    connect(start, SIGNAL(clicked(bool)), this, SLOT(initializeGame()));
    connect(cancel, SIGNAL(clicked(bool)), this, SLOT(close()));

}


void GameStart::initializeGame()
{
    int time;
    time = timeSet->text().toInt();
    clock->initialize(time);
    board->initialize(black->isChecked() ? Board::Color::BLACK : Board::Color::WHITE);
    this->close();
}

