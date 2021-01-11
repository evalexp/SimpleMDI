#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->initMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::newFile
 * init a new subwin
 */
void MainWindow::newFile()
{
    auto *mdiWin = new MySubWin();
    auto *textEdit = new QTextEdit();
    mdiWin->setWidget(textEdit);
    mdiWin->setWindowTitle("Untitled");
    mdiWin->setAttribute(Qt::WA_DeleteOnClose, true);
    connect(textEdit, &QTextEdit::textChanged, this, &MainWindow::ContentChange);
    connect(mdiWin, &MySubWin::sendClose, this, &MainWindow::subWinCloseEvent);
    connect(textEdit, &QTextEdit::cursorPositionChanged, this, &MainWindow::resetFontSelection);
    ui->mdiArea->addSubWindow(mdiWin);
    mdiWin->show();
}

/**
 * @brief MainWindow::initMenu
 * init menu and the toolbar
 */
void MainWindow::initMenu(){
    QMenu *menuFile = ui->menubar->addMenu("文件");
    QAction *newFile = new QAction("新建", this);
    newFile->setIcon(QIcon(QPixmap(":/images/icon/newFile.ico")));
    newFile->setShortcut(QKeySequence::New);
    connect(newFile, &QAction::triggered, this, &MainWindow::newFile);
    QAction *open = new QAction("打开", this);
    open->setShortcut(QKeySequence::Open);
    open->setIcon(QIcon(QPixmap(":/images/icon/open.ico")));
    connect(open, &QAction::triggered, this, &MainWindow::OpenFile);
    QAction *save = new QAction("保存", this);
    save->setShortcut(QKeySequence::Save);
    save->setIcon(QIcon(QPixmap(":/images/icon/save.png")));
    connect(save, &QAction::triggered, this, &MainWindow::SaveFile);
    QAction *saveAs = new QAction("另存为", this);
    saveAs->setShortcut(QKeySequence("F12"));
    connect(saveAs, &QAction::triggered, this, &MainWindow::SaveAs);
    saveAs->setIcon(QIcon(QPixmap(":/images/icon/saveas.png")));
    QAction *close = new QAction("关闭", this);
    close->setShortcut(QKeySequence::Close);
    close->setIcon(QIcon(QPixmap(":/images/icon/close.png")));
    connect(close, &QAction::triggered, this, &MainWindow::CloseSubWin);

    menuFile->addAction(newFile);
    menuFile->addAction(open);
    menuFile->addAction(save);
    menuFile->addAction(saveAs);
    menuFile->addSeparator();
    menuFile->addAction(close);

    QMenu *menuWindow = ui->menubar->addMenu("窗口");
    QAction *cascade = new QAction("窗口层叠", this);
    cascade->setShortcut(QKeySequence("Alt+C"));
    cascade->setIcon(QIcon(QPixmap(":/images/icon/cascade.png")));
    connect(cascade, &QAction::triggered, this, [=](){ui->mdiArea->cascadeSubWindows();});
    QAction *horTile = new QAction("水平平铺", this);
    horTile->setShortcut(QKeySequence("Alt+H"));
    horTile->setIcon(QIcon(QPixmap(":/images/icon/hor.png")));
    connect(horTile, &QAction::triggered, this, [=](){this->setTile(TILE_TYPE::HOR);});
    QAction *verTile = new QAction("垂直平铺", this);
    verTile->setShortcut(QKeySequence("Alt+V"));
    verTile->setIcon(QIcon(QPixmap(":/images/icon/ver.png")));
    connect(verTile, &QAction::triggered, this, [=](){this->setTile(TILE_TYPE::VER);});
    QAction *gridTile = new QAction("栅格平铺", this);
    gridTile->setShortcut(QKeySequence("Alt+G"));
    gridTile->setIcon(QIcon(QPixmap(":/images/icon/grid.png")));
    connect(gridTile, &QAction::triggered, this, [=](){ui->mdiArea->tileSubWindows();});
    menuWindow->addAction(cascade);
    menuWindow->addAction(horTile);
    menuWindow->addAction(verTile);
    menuWindow->addAction(gridTile);

    QToolBar *toolBar = addToolBar("ToolBar");
    fontSelction = new QComboBox;
    QFontDatabase *qfd = new QFontDatabase;
    fontSelction->addItem("");
    for(auto &family: qfd->families()){
        fontSelction->addItem(family);
    }
    connect(fontSelction, &QComboBox::currentTextChanged, this, &MainWindow::setFont);
    fontSelction->setToolTip("设置为选择字体");
    delete qfd;
    QAction *bold = new QAction("加粗", this);
    bold->setIcon(QIcon(QPixmap(":/images/icon/bold.png")));
    connect(bold, &QAction::triggered, this, &MainWindow::setBold);
    QAction *italic = new QAction("斜体", this);
    italic->setIcon(QIcon(QPixmap(":/images/icon/italic.png")));
    connect(italic, &QAction::triggered, this, &MainWindow::setItalic);
    QAction *underscode = new QAction("下划线", this);
    underscode->setIcon(QIcon(QPixmap(":/images/icon/underscode.png")));
    connect(underscode, &QAction::triggered, this, &MainWindow::setUnderline);
    QAction *undo = new QAction("撤销");
    undo->setIcon(QIcon(QPixmap(":/images/icon/undo.png")));
    connect(undo, &QAction::triggered, this, &MainWindow::undo);
    QAction *redo = new QAction("重做");
    redo->setIcon(QIcon(QPixmap(":/images/icon/redo.png")));
    connect(redo, &QAction::triggered, this, &MainWindow::redo);
    QAction *left = new QAction("左对齐");
    QAction *right = new QAction("右对齐");
    QAction *mid = new QAction("居中");
    left->setIcon(QIcon(QPixmap(":/images/icon/left.png")));
    mid->setIcon(QIcon(QPixmap(":/images/icon/mid.png")));
    right->setIcon(QIcon(QPixmap(":/images/icon/right.png")));
    connect(left, &QAction::triggered, this, [=](){this->setAlignment(ALIGNMENT::LEFT);});
    connect(right, &QAction::triggered, this, [=](){this->setAlignment(ALIGNMENT::RIGHT);});
    connect(mid, &QAction::triggered, this, [=](){this->setAlignment(ALIGNMENT::MID);});
    toolBar->addAction(newFile);
    toolBar->addAction(open);
    toolBar->addAction(save);
    toolBar->addSeparator();
    toolBar->addWidget(fontSelction);
    toolBar->addAction(bold);
    toolBar->addAction(italic);
    toolBar->addAction(underscode);
    toolBar->addSeparator();
    toolBar->addAction(undo);
    toolBar->addAction(redo);
    toolBar->addAction(left);
    toolBar->addAction(mid);
    toolBar->addAction(right);
}

/**
 * @brief MainWindow::getFileName
 * @param path
 * @return filename
 * get the filename from the path
 */
QString MainWindow::getFileName(const QString &path){
    QStringList strList = path.split("/");
    return strList[strList.length() - 1];
}

/**
 * @brief MainWindow::setAlignment
 * @param type The type of alignment
 * set the text edit align tyoe
 */
void MainWindow::setAlignment(ALIGNMENT type){
    QTextEdit* edit;
    MySubWin* subWin;
    if(this->GetEditAndSubwin(edit, subWin)){
        switch (type) {
        case ALIGNMENT::LEFT:
            edit->setAlignment(Qt::AlignLeft);
            break;
        case ALIGNMENT::MID:
            edit->setAlignment(Qt::AlignCenter);
            break;
        case ALIGNMENT::RIGHT:
            edit->setAlignment(Qt::AlignRight);
            break;
        }
    }

}

/**
 * @brief MainWindow::undo
 * textedit undo
 */
void MainWindow::undo(){
    QTextEdit *edit;
    MySubWin *subWin;
    if(this->GetEditAndSubwin(edit, subWin)){
        edit->undo();
    }
}

/**
 * @brief MainWindow::redo
 * textedit redo
 */
void MainWindow::redo(){
    QTextEdit *edit;
    MySubWin *subWin;
    if(this->GetEditAndSubwin(edit, subWin)){
        edit->redo();
    }
}

/**
 * @brief MainWindow::setTile
 * @param type  The type that will tile
 */
void MainWindow::setTile(TILE_TYPE type){
    double ver = 0, hor = 0;
    auto height = ui->mdiArea->size().height();
    auto width = ui->mdiArea->size().width();
    auto winList = ui->mdiArea->subWindowList();
    switch (type) {
        case TILE_TYPE::VER:
            ver = 1;
            width /= winList.length();
            break;
        case TILE_TYPE::HOR:
            hor = 1;
            height /= winList.length();
            break;
    }
    for(auto i = 0; i < winList.length(); i++){
        winList[i]->setGeometry((0 + width * i) * ver, (0 + height * i) * hor, width, height);
    }
}

/**
 * @brief MainWindow::SaveFile
 * slot of save action
 * if the filename unknown, then call save as action
 */
void MainWindow::SaveFile(){
    QTextEdit *edit;
    MySubWin *subWin;
    if(!this->GetEditAndSubwin(edit, subWin))    return ;
    if(subWin->windowTitle() == "Untitled" || subWin->windowTitle() == "Untitled*"){
        this->SaveAs();
    }else{
        if(!FileHelper::write(edit->documentTitle(), edit->toHtml())){
            QMessageBox::critical(this, "ERROR", "抱歉，保存文件失败，可能有其它程序占用了该文件。");
        }else{
            if(subWin->windowTitle()[subWin->windowTitle().length() - 1] == '*'){
                subWin->setWindowTitle(subWin->windowTitle().left(subWin->windowTitle().length() - 2));
            }
        }
    }
}

/**
 * @brief MainWindow::SaveAs
 * slot of saveas action
 */
void MainWindow::SaveAs(){
    QTextEdit* edit;
    MySubWin *subWin;
    if(this->GetEditAndSubwin(edit, subWin)){
        QString fileName = QFileDialog::getSaveFileName(this, "保存文件", "../Untitled", "Rich Text Format (*.rtf)");
        if(fileName != ""){
            if(FileHelper::write(fileName, edit->toHtml())){
                subWin->setWindowTitle(this->getFileName(fileName));
                edit->setDocumentTitle(fileName);
            }else{
                QMessageBox::critical(this, "ERROR", "抱歉，保存文件失败，可能有其它程序占用了该文件。");
            }
        }
    }
}

/**
 * @brief MainWindow::GetEditAndSubwin
 * @param edit  the ref pointer of QTextEdit
 * @param subWin    the ref pointer of QMdiSubWindow
 * @return if get it's pointer successful
 */
bool MainWindow::GetEditAndSubwin(QTextEdit* &edit, MySubWin* &subWin){
    if(ui->mdiArea->subWindowList().length() == 0){
        return false;
    }else{
        subWin = (MySubWin*)ui->mdiArea->activeSubWindow();
        edit = (QTextEdit*)ui->mdiArea->activeSubWindow()->widget();
        return true;
    }
}

/**
 * @brief MainWindow::ContentChange
 * when content change, marked the unsave subwin
 */
void MainWindow::ContentChange(){
    QTextEdit *edit;
    MySubWin *subWin;
    if(this->GetEditAndSubwin(edit, subWin)){
        if(subWin->windowTitle()[subWin->windowTitle().length() - 1] != '*')
            subWin->setWindowTitle(subWin->windowTitle() + "*");
    }
}

/**
 * @brief MainWindow::CloseSubWin
 * from menu close subwin
 */
void MainWindow::CloseSubWin(){
    QTextEdit *edit;
    MySubWin *subWin;
    if(this->GetEditAndSubwin(edit, subWin)){
        subWin->close();
    }
}

/**
 * @brief MainWindow::subWinCloseEvent
 * subWin.close() will send signal to this
 */
void MainWindow::subWinCloseEvent(){
    QTextEdit *edit;
    MySubWin *subWin;
    if(this->GetEditAndSubwin(edit, subWin)){
        if(subWin->windowTitle()[subWin->windowTitle().length() - 1] == '*'){
            auto result = QMessageBox::question(this, "未保存", "当前文档尚未保存，是否进行保存？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            switch (result) {
            case QMessageBox::Yes:
                this->SaveFile();
                break;
            case QMessageBox::No:
                break;
            default:
                break;
            }
        }
    }
}

/**
 * @brief MainWindow::OpenFile
 * if file subWin exist, active it
 * if not exist, create a new subWin and set all the properties
 */
void MainWindow::OpenFile(){
    auto fileName = QFileDialog::getOpenFileName(this, "打开文件", "", "Rich Text Format (*.rtf)");
    if(!fileName.isNull()){
        for(auto &item : ui->mdiArea->subWindowList()){
            if(((QTextEdit*)item->widget())->documentTitle() == fileName){
                ui->mdiArea->setActiveSubWindow(item);
                return ;
            }
        }
        QString content;
        if(FileHelper::read(fileName, content)){
            this->newFile();
            QTextEdit* edit;
            MySubWin *subWin;
            if(this->GetEditAndSubwin(edit, subWin)){
                edit->setHtml(content);
                edit->setDocumentTitle(fileName);
                subWin->setWindowTitle(this->getFileName(fileName));
            }
        }else{
            QMessageBox::critical(this, "ERROR", "无法打开该文件！");
        }
    }
}

/**
 * @brief MainWindow::resetFontSelection
 * set the combobox current text to selected text's fontfamily
 */
void MainWindow::resetFontSelection(){
    QTextEdit* edit;
    MySubWin *subwin;
    if(this->GetEditAndSubwin(edit, subwin)){
        auto fmt = edit->textCursor().charFormat();
        this->fontSelction->blockSignals(true);
        this->fontSelction->setCurrentText(fmt.fontFamily());
        this->fontSelction->blockSignals(false);
    }
}

/**
 * @brief MainWindow::setFont
 * fontfamily style merge
 */
void MainWindow::setFont(){
    QTextEdit* edit;
    MySubWin *subwin;
    if(this->GetEditAndSubwin(edit, subwin)){
        auto cursor = edit->textCursor();
        auto fmt = QTextCharFormat();
        fmt.setFontFamily(this->fontSelction->currentText());

        edit->textCursor().mergeCharFormat(fmt);
    }
}

/**
 * @brief MainWindow::setBold
 * bold style merge
 */
void MainWindow::setBold(){
    QTextEdit* edit;
    MySubWin *subwin;
    if(this->GetEditAndSubwin(edit, subwin)){
        auto fmt = QTextCharFormat();
        if(edit->textCursor().charFormat().fontWeight() == QFont::Weight::Bold){
            fmt.setFontWeight(QFont::Weight::Thin);
        }else{
            fmt.setFontWeight(QFont::Weight::Bold);
        }
        edit->textCursor().mergeCharFormat(fmt);
    }
}

/**
 * @brief MainWindow::setItalic
 * italic style merge
 */
void MainWindow::setItalic(){
    QTextEdit* edit;
    MySubWin* subWin;
    if(this->GetEditAndSubwin(edit, subWin)){
        auto fmt = QTextCharFormat();
        if(edit->textCursor().charFormat().fontItalic()){
            fmt.setFontItalic(false);
        }else{
            fmt.setFontItalic(true);
        }
        edit->textCursor().mergeCharFormat(fmt);
    }
}

/**
 * @brief MainWindow::setUnderline
 * underline style merge
 */
void MainWindow::setUnderline(){
    QTextEdit* edit;
    MySubWin* subWin;
    if(this->GetEditAndSubwin(edit, subWin)){
        auto fmt = QTextCharFormat();
        if(edit->textCursor().charFormat().fontUnderline()){
            fmt.setFontUnderline(false);
        }else{
            fmt.setFontUnderline(true);
        }
        edit->textCursor().mergeCharFormat(fmt);
    }
}
