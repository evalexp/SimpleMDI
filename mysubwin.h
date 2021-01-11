#ifndef MYSUBWIN_H
#define MYSUBWIN_H
#include "QCloseEvent"
#include "QMdiSubWindow"
#include "QDebug"
class MySubWin: public QMdiSubWindow
{
    Q_OBJECT
public:
    MySubWin();
    void closeEvent(QCloseEvent *event);

signals:
    void sendClose();
private:
};

#endif // MYSUBWIN_H
