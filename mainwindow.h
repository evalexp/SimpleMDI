#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QMdiSubWindow"
#include "QComboBox"
#include "QFileDialog"
#include "QFile"
#include "QMessageBox"
#include "QTextEdit"
#include "filehelper.h"
#include "mysubwin.h"
#include "QTextBlock"
#include "QDebug"
#include "QToolBar"
#include "QPushButton"
#include "QFontDatabase"
#include "mysubwin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

    void initMenu();

    enum TILE_TYPE{HOR, VER};
    enum ALIGNMENT{LEFT, MID, RIGHT};
    QComboBox *fontSelction;

    void setFont();
    void setBold();
    void setItalic();
    void setUnderline();
    QString getFileName(const QString& path);

private slots:
    void newFile();
    void setTile(TILE_TYPE);
    void SaveFile();
    void SaveAs();
    bool GetEditAndSubwin(QTextEdit*&, MySubWin*&);
    void ContentChange();
    void CloseSubWin();
    void OpenFile();
    void undo();
    void redo();
    void setAlignment(ALIGNMENT type);

    void subWinCloseEvent();

    void resetFontSelection();
};
#endif // MAINWINDOW_H
