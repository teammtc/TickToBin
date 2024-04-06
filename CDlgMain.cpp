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

    QString sTrFilePath = "D:/스터디/시세/U20240116/tr_list_240406.txt";
    QFile fTrFile(sTrFilePath);
    if(fTrFile.open(QIODevice::ReadOnly | QIODevice::Text) == false)
    {
        qDebug() << "Failed to open TR file";
        return;
    }

    QTextStream tsTrStream(&fTrFile);
    QStringList slTrList;
    QString     sReadLine;

    for (;;)
    {
        if (tsTrStream.atEnd() == false)
        {
            sReadLine = tsTrStream.readLine();
            slTrList << sReadLine.split(',');
        }
        else
        {
            if (fTrFile.isOpen() == true)
                fTrFile.close();

            break;
        }
    }

    QStringList slAddTrList, slDelTrList;

    // 범위(~) 개별TR로 변경
    for (auto&& trUnit : slTrList)
    {
        trUnit = trUnit.remove(' ');

        if (trUnit.indexOf('~') > 0)
        {
            slDelTrList << trUnit;
            QString sStartTr = trUnit.left(trUnit.indexOf('~')    );
            QString sEndTr   = trUnit.mid (trUnit.indexOf('~') + 1);

            int iStartNum = sStartTr.mid(1, 3).toInt();
            int iEndNum   = sEndTr.mid(1, 3).toInt();

            for (int iIdx = iStartNum; iIdx <= iEndNum; ++iIdx)
            {
                QString sAddTrNm = trUnit.at(0) +
                                   QString("%1").arg(iIdx, 3, 10, QChar('0')) +
                                   trUnit.at(4);
                slAddTrList << sAddTrNm;
            }
        }
    }

    for (auto&& delTr : slDelTrList)
        slTrList.removeOne(delTr);

    slTrList << slAddTrList;

    for (auto&& trUnit : slTrList)
    {
        trInfo_ST trInfo_st;
        mReqTrMap.insert(trUnit, trInfo_st);
    }
}

CDlgMain::~CDlgMain()
{
    delete ui;
}

void CDlgMain::slotBtnOpenFile(void)
{
    QString sFileName = QFileDialog::getOpenFileName(nullptr
                                                     , tr("Open File")
                                                     , tr("D:/스터디/시세/U20240116/")
                                                     , tr("Text files (*.txt)"));

    if (sFileName.isEmpty() == true)
    {
        qDebug() << "Failed to get file name";
        return;
    }

    mFile.setFileName(sFileName);
    if(mFile.open(QIODevice::ReadOnly | QIODevice::Text) == false)
    {
        qDebug() << "Failed to open " << sFileName << " file";
        return;
    }

    mTextStream.setDevice(&mFile);
    mTextStream.setEncoding(QStringConverter::System);
    readNextLine();
}

void CDlgMain::slotBtnNextTR(void)
{
    readNextLine();
}

void CDlgMain::readNextLine(void)
{
    QString sReadLine;

    for (;;)
    {
        if (mTextStream.atEnd() == false)
        {
            sReadLine = mTextStream.readLine();

            if (sReadLine.length() >= mColonPos && sReadLine.at(mColonPos) == ':')
            {
                ui->teLog1->setText(sReadLine.mid(mColonPos + 1));

                // EpochTime 변환
                qint64 iEpochTime = sReadLine.left(mColonPos).toLongLong();
                iEpochTime = iEpochTime / 1000;
                QDateTime dDateTime = dDateTime.fromMSecsSinceEpoch(iEpochTime);
                ui->leRcvTM->setText(dDateTime.toString("HH:mm:ss.zzz"));
                break;
            }
        }
        else
        {
            if (mFile.isOpen() == true)
                mFile.close();

            ui->teLog1->setText("end of file");
            return;
        }
    }

    return;
}
