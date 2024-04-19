#include "CThDataReader.hpp"
#include <QDebug>

CThDataReader::CThDataReader()
{
    mpFile = std::make_unique<QFile>();
}

CThDataReader::~CThDataReader()
{

}

ThStatus CThDataReader::getStatus()
{
    return mStatus;
}

void CThDataReader::setStatus(ThStatus status)
{
    mStatus = status;
}

void CThDataReader::slotPrepareFile(QString strFile)
{
    if (strFile.isEmpty() == true)
    {
        qDebug() << "Failed to get file name";
        return;
    }

    mpFile->setFileName(strFile);
    if(mpFile->open(QIODevice::ReadOnly | QIODevice::Text) == false)
    {
        qDebug() << "Failed to open " << strFile << " file";
        return;
    }
    mTextStream.setDevice(mpFile.get());
    mTextStream.setEncoding(QStringConverter::System);
}

void CThDataReader::processReading()
{
    QString sReadLine, sTrText, sTrCode;
    QByteArray tmpByteArr;

    while (true)
    {
        if (mTextStream.atEnd() == false)
        {
            sReadLine = mTextStream.readLine();
            qDebug() << sReadLine;

            // // epoch time이 마이크로 단위라 16자리
            // // 따라서 읽은 Line이 16자리 이상이고 그다음 콜론(:)이 온다면 유효한 TR로 간주
            // if (sReadLine.length() >= mCOLON_POS && sReadLine.at(mCOLON_POS) == ':')
            // {
            //     sTrText = sReadLine.mid(mCOLON_POS + 1);
            //     sTrCode = sTrText.left(mTR_CODE_LEN);

            //     auto iterReqTrMap = mReqTrMap.find(sTrCode);

            //     // 버릴 수 없는 TR목록에 포함되면 처리
            //     if (iterReqTrMap != mReqTrMap.end())
            //     {
            //         // 한글자리수 계산을 위해 ByteArr 사용
            //         tmpByteArr = sTrText.toLocal8Bit();

            //         if (tmpByteArr.length() + 1 == iterReqTrMap.value().mLength)
            //         {
            //             ui->teLog1->setText(sTrText);

            //             // EpochTime 변환
            //             qint64 iEpochTime = sReadLine.left(mCOLON_POS).toLongLong();
            //             iEpochTime = iEpochTime / 1000;
            //             QDateTime dDateTime = dDateTime.fromMSecsSinceEpoch(iEpochTime);
            //             ui->leRcvTM->setText(dDateTime.toString("HH:mm:ss.zzz"));
            //             break;
            //         }
            //         else
            //         {
            //             ui->teLog1->setText(sTrCode + " 정상수신실패");
            //             break;
            //         }
            //     }
            // }
        }
        else
        {
            if (mpFile->isOpen() == true)
            {
                mpFile->reset();
            }
        }
    }

}

void CThDataReader::run()
{
    while(true)
    {
        switch(mStatus)
        {
        case ThStatus::Init:
            qDebug() << "Starting the data reader..";
            setStatus(ThStatus::Running);
            break;

        case ThStatus::Running:
            processReading();
            break;

        case ThStatus::Stopped:
            break;
        }
    }
};
