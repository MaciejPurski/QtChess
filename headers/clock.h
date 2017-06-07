#ifndef CLOCK_H
#define CLOCK_H
#include <QWidget>
#include <QTimer>
#include <QLayout>
#include <QLabel>
#include <QTime>
#include <QDebug>
#include <QPushButton>

class Clock : public QWidget
{
    Q_OBJECT
public:
    explicit Clock(QWidget *parent = 0);
    void initialize(int minutes);

private:
    QTime counter, blackT, whiteT;
    QTimer *timer;
    QLabel *blackText, *whiteText, *blackName, *whiteName;
    QVBoxLayout *black, *white;
    QPushButton *test;
    QHBoxLayout *main;

private slots:
    void updateTime();


};

#endif // CLOCK_H
