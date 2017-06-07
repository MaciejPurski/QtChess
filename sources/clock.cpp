#include "clock.h"
#include "game.h"


Clock::Clock (QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(300, 200);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);


    whiteText = new QLabel("00:00");
    blackText = new QLabel("00:00");
    blackName = new QLabel("Black");
    whiteName = new QLabel("White");
    main = new QHBoxLayout(this);
    white = new QVBoxLayout();
    black = new QVBoxLayout();
    black->addWidget(blackName);
    black->addWidget(blackText);
    white->addWidget(whiteName);
    white->addWidget(whiteText);
    main->addLayout(white);
    main->addLayout(black);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime(void)));
}

void Clock::initialize(int minutes)
{
    QString temp;
    temp.setNum(minutes);
    temp=temp + ":00";
    whiteText->setText(temp);
    blackText->setText(temp);

    whiteT.setHMS(0, minutes, 0);
    blackT.setHMS(0, minutes, 0);

    Game::state=Game::WhiteMove;
    timer->start(1000);
}

void Clock::updateTime()
{
    QString temp;

    if(Game::state==Game::WhiteMove)
    {
        whiteT=whiteT.addSecs(-1);
        temp=whiteT.toString("mm:ss");
        whiteText->setText(temp);
        if(temp == "00::00") {
            Game::state = Game::Finished;
            Game::checkState = Game::WhiteMat;
        }
    }
    else if(Game::state==Game::BlackMove)
    {
        blackT=blackT.addSecs(-1);
        temp=blackT.toString("mm:ss");
        blackText->setText(temp);
        if(temp == "00::00") {
            Game::state = Game::Finished;
            Game::checkState = Game::BlackMat;
        }
    }
}


