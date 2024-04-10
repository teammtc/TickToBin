#include "CDlgMain.hpp"
#include "ui_CDlgMain.h"
#include <QFileDialog>

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
    // .txt 형태의 파일을 선택할 수 있는 다이얼로그
    QString filename = QFileDialog::getOpenFileName(this, "파일 선택", QDir::currentPath(), "Files (*.txt)");
    qDebug() << "filename: " << filename;

    mFile.setFileName(filename);
    if(mFile.open(QIODevice::ReadOnly | QIODevice::Text) == false)
    {
        ui->teLog1->setText(tr("파일 여는 중 에러 발생"));
        return;
    }

    mTxtStream.setDevice(&mFile);
    // 텍스트 스트림이 어떤 방식으로 디코딩 할 것인지 결정해 준다.
    // QStringConverter::System을 채택 -> 현재 시스템의 로캘 정보를 그대로 적용해 주도록 설정.
    mTxtStream.setEncoding(QStringConverter::System);
}

void CDlgMain::slotBtnNextTR(void)
{
    QString strLine, strTmp;

    while (!mTxtStream.atEnd())
    {
        strLine = mTxtStream.readLine();

        // 'I702S' 등과 같이 첫 5자리의 TR 문자열만을 추려낸다.
        strTmp = strLine.mid(lenEpochTime + 1);
        QString strTmpTrCode = strTmp.mid(0, 5);
        qDebug() << strTmpTrCode;

        // TR 정보는 16자리의 epoch time 그리고 콜론으로 시작하므로, 이 라인들만 골라내기 위한 조건
        // 1705351201881283:I702S00000010KRA5812AXDB30001720231127202408010000000001000000000000R0000000000015.0000000000000000003000300000000000000000000.000000000000000005000.000000000000000000000.000000000000000000000.000
        // 추려낸 TR이 버릴 수 없는 TR 목록에 들어가 있는지 여부를 먼저 확인.
        if (strLine.length() >= lenEpochTime && strLine.at(lenEpochTime) == ':' && mTR_CODE_SIZE.contains(strTmpTrCode))
        {
            QByteArray bytes = strTmp.toUtf8();
            qDebug() << "length: " << bytes.length();

            ui->teLog1->setText(strTmp);

            qint64 epochTime = strLine.left(lenEpochTime).toLongLong();
            epochTime = epochTime / 1000;
            QDateTime dateTime = dateTime.fromMSecsSinceEpoch(epochTime);
            ui->leRcvTM->setText(dateTime.toString("HH:mm:ss.zzz"));
            break;
        }
    }
    mFile.close();
    return;
}
