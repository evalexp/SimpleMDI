#include "mysubwin.h"

MySubWin::MySubWin()
{

}

void MySubWin::closeEvent(QCloseEvent *event){
    sendClose();
    event->accept();
}
