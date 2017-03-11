#ifndef QUITWINDOW_H
#define QUITWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QMessageBox>

class QuitWindow : QMessageBox
{
    Q_OBJECT
public:
    QuitWindow();
public slots:

private:
    QPushButton *yes, *no;
};

#endif // QUITWINDOW_H
