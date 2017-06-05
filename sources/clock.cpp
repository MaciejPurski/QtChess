#include "clock.h"
#include "game.h"


Clock::Clock (QWidget *parent) : QWidget(parent)
{

    this->setFixedSize(300, 200);
    whiteText = new QLabel("00:00");
    blackText = new QLabel("00:00");

    test = new QPushButton("OK");

    main = new QHBoxLayout(this);
    main->addWidget(whiteText);
    main->addWidget(blackText);
    main->addWidget(test);



    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime(void)));
    connect(test, SIGNAL(clicked(bool)), this, SLOT(newTurn()));
}

void Clock::initialize(int minutes)
{

    QString temp;
    temp.setNum(minutes);
    temp=temp + ":00";
    whiteText->setText(temp);
    blackText->setText(temp);

    white.setHMS(0, minutes, 0);
    black.setHMS(0, minutes, 0);

    Game::state=Game::WhiteMove;
    timer->start(1000);
}

void Clock::updateTime()
{
    QString temp;

    if(Game::state==Game::WhiteMove)
    {
        white=white.addSecs(-1);
        temp=white.toString("mm:ss");
        whiteText->setText(temp);
    }
    else if(Game::state==Game::BlackMove)
    {
        black=black.addSecs(-1);
        temp=black.toString("mm:ss");
        blackText->setText(temp);
    }
}



