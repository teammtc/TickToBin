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

    QString sTrFilePath = ":/tr_list_240406.txt";
    QFile fTrFile(sTrFilePath);
    if(fTrFile.open(QIODevice::ReadOnly | QIODevice::Text) == false)
    {
        qDebug() << "Failed to open TR file";
        return;
    }

    // TR목록파일을 QMap에 Insert
    QTextStream tsTrStream(&fTrFile);
    QStringList slSplitList;
    QString     sReadLine;
    trInfo_ST trInfo_st;

    for (;;)
    {
        if (tsTrStream.atEnd() == false)
        {
            sReadLine = tsTrStream.readLine();
            trInfo_st.mLength = sReadLine.mid(sReadLine.indexOf(':') + 1).toInt();

            slSplitList.clear();
            slSplitList << sReadLine.split(',');

            // 범위(~) 개별TR로 변경
            for (auto&& trUnit : slSplitList)
            {
                trUnit = trUnit.remove(' ');

                if (trUnit.indexOf('~') > 0)
                {
                    QString sStartTr = trUnit.left(trUnit.indexOf('~')    );
                    QString sEndTr   = trUnit.mid (trUnit.indexOf('~') + 1);

                    int iStartNum = sStartTr.mid(1, 3).toInt();
                    int iEndNum   = sEndTr.mid(1, 3).toInt();

                    for (int iIdx = iStartNum; iIdx <= iEndNum; ++iIdx)
                    {
                        QString sAddTrCode = trUnit.at(0) +
                                             QString("%1").arg(iIdx, 3, 10, QChar('0')) +
                                             trUnit.at(4);
                        mReqTrMap.insert(sAddTrCode, trInfo_st);
                    }
                }
                else
                    mReqTrMap.insert(trUnit.left(mTrCodeLen), trInfo_st);
            }
        }
        else
        {
            if (fTrFile.isOpen() == true)
                fTrFile.close();

            break;
        }
    }

    /* QMap데이터 확인
    QMapIterator<QString, trInfo_ST> iter(mReqTrMap);
    while (iter.hasNext())
    {
        iter.next();
        qDebug() << iter.key() << " " << iter.value().mLength;
    }
    */
}

CDlgMain::~CDlgMain()
{
    delete ui;
}

void CDlgMain::slotBtnOpenFile(void)
{
    QString sFileName = QFileDialog::getOpenFileName(nullptr
                                                     , tr("Open File")
                                                     , QDir::homePath()
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
    QString sReadLine, sTrText, sTrCode;
    QByteArray tmpByteArr;

    for (;;)
    {
        if (mTextStream.atEnd() == false)
        {
            sReadLine = mTextStream.readLine();

            if (sReadLine.length() >= mColonPos && sReadLine.at(mColonPos) == ':')
            {
                sTrText = sReadLine.mid(mColonPos + 1);
                sTrCode = sTrText.left(mTrCodeLen);

                auto iterReqTrMap = mReqTrMap.find(sTrCode);

                if (iterReqTrMap != mReqTrMap.end())
                {
                    tmpByteArr = sTrText.toLocal8Bit();

                    if (tmpByteArr.length() + 1 == iterReqTrMap.value().mLength)
                    {
                        ui->teLog1->setText(sTrText);

                        // EpochTime 변환
                        qint64 iEpochTime = sReadLine.left(mColonPos).toLongLong();
                        iEpochTime = iEpochTime / 1000;
                        QDateTime dDateTime = dDateTime.fromMSecsSinceEpoch(iEpochTime);
                        ui->leRcvTM->setText(dDateTime.toString("HH:mm:ss.zzz"));
                        break;
                    }
                    else
                    {
                        ui->teLog1->setText(sTrCode + " 정상수신실패");
                        break;
                    }
                }
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
