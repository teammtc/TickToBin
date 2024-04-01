#include "CDlgMain.hpp"
#include "ui_CDlgMain.h"

CDlgMain::CDlgMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CDlgMain)
{
    ui->setupUi(this);

    QString iStr2 = "v0.01 <2024.03.25(01)>";

#if DEBUG
    this->setWindowTitle("TickToBin (DEBUG Mode) " + iStr2);
#elif RELEASE
    this->setWindowTitle("TickToBin " + iStr2);
#endif
}

CDlgMain::~CDlgMain()
{
    delete ui;
}

void CDlgMain::slotBtnOpenFile(void)
{
    QString sFileName = QFileDialog::getOpenFileName(nullptr, tr("Open File"), "D:/스터디/시세/U20240116", tr("Text files (*.txt)"));
}

void CDlgMain::slotBtnNextTR(void)
{

}
