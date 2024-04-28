#include "CThDataReader.hpp"
#include <QDebug>
#include <QDateTime>

CThDataReader::CThDataReader()
{
    // TR코드와 길이 초기화
    // 파일로 관리 시 Integrity 훼손 위험 존재하여 하드코딩으로 전환
    QVector<QPair<QString, int16_t>> initVec;
    initVec.append(qMakePair("B601S", 555));
    initVec.append(qMakePair("B601Q", 555));

    initVec.append(qMakePair("B702S", 795));
    initVec.append(qMakePair("B703S", 795));
    initVec.append(qMakePair("B704S", 795));

    initVec.append(qMakePair("A301S", 186));
    initVec.append(qMakePair("A302S", 186));
    initVec.append(qMakePair("A303S", 186));
    initVec.append(qMakePair("A304S", 186));
    initVec.append(qMakePair("A301Q", 186));

    initVec.append(qMakePair("G701S", 648));
    initVec.append(qMakePair("G701Q", 648));

    initVec.append(qMakePair("G702S", 888));
    initVec.append(qMakePair("G703S", 888));
    initVec.append(qMakePair("G704S", 888));

    initVec.append(qMakePair("A701S", 68));
    initVec.append(qMakePair("A702S", 68));
    initVec.append(qMakePair("A703S", 68));
    initVec.append(qMakePair("A704S", 68));
    initVec.append(qMakePair("A701Q", 68));
    initVec.append(qMakePair("A701F", 68));
    initVec.append(qMakePair("A702F", 68));
    initVec.append(qMakePair("A703F", 68));
    initVec.append(qMakePair("A704F", 68));
    initVec.append(qMakePair("A705F", 68));
    initVec.append(qMakePair("A706F", 68));
    initVec.append(qMakePair("A707F", 68));
    initVec.append(qMakePair("A708F", 68));
    initVec.append(qMakePair("A709F", 68));
    initVec.append(qMakePair("A710F", 68));
    initVec.append(qMakePair("A711F", 68));
    initVec.append(qMakePair("A712F", 68));
    initVec.append(qMakePair("A713F", 68));
    initVec.append(qMakePair("A714F", 68));
    initVec.append(qMakePair("A715F", 68));
    initVec.append(qMakePair("A716F", 68));
    initVec.append(qMakePair("A701G", 68));
    initVec.append(qMakePair("A701E", 68));

    initVec.append(qMakePair("B601F", 315));
    initVec.append(qMakePair("B602F", 315));
    initVec.append(qMakePair("B603F", 315));
    initVec.append(qMakePair("B606F", 315));
    initVec.append(qMakePair("B607F", 315));
    initVec.append(qMakePair("B608F", 315));
    initVec.append(qMakePair("B609F", 315));
    initVec.append(qMakePair("B610F", 315));
    initVec.append(qMakePair("B611F", 315));
    initVec.append(qMakePair("B612F", 315));
    initVec.append(qMakePair("B613F", 315));
    initVec.append(qMakePair("B614F", 315));
    initVec.append(qMakePair("B615F", 315));
    initVec.append(qMakePair("B616F", 315));

    initVec.append(qMakePair("B604F", 545));
    initVec.append(qMakePair("B605F", 545));

    initVec.append(qMakePair("A301F", 173));
    initVec.append(qMakePair("A302F", 173));
    initVec.append(qMakePair("A303F", 173));
    initVec.append(qMakePair("A304F", 173));
    initVec.append(qMakePair("A305F", 173));
    initVec.append(qMakePair("A306F", 173));
    initVec.append(qMakePair("A307F", 173));
    initVec.append(qMakePair("A308F", 173));
    initVec.append(qMakePair("A309F", 173));
    initVec.append(qMakePair("A310F", 173));
    initVec.append(qMakePair("A311F", 173));
    initVec.append(qMakePair("A312F", 173));
    initVec.append(qMakePair("A313F", 173));
    initVec.append(qMakePair("A314F", 173));
    initVec.append(qMakePair("A315F", 173));
    initVec.append(qMakePair("A316F", 173));

    initVec.append(qMakePair("G701F", 431));
    initVec.append(qMakePair("G702F", 431));
    initVec.append(qMakePair("G703F", 431));
    initVec.append(qMakePair("G706F", 431));
    initVec.append(qMakePair("G707F", 431));
    initVec.append(qMakePair("G708F", 431));
    initVec.append(qMakePair("G709F", 431));
    initVec.append(qMakePair("G710F", 431));
    initVec.append(qMakePair("G711F", 431));
    initVec.append(qMakePair("G712F", 431));
    initVec.append(qMakePair("G713F", 431));
    initVec.append(qMakePair("G714F", 431));
    initVec.append(qMakePair("G715F", 431));
    initVec.append(qMakePair("G716F", 431));

    initVec.append(qMakePair("G704F", 661));
    initVec.append(qMakePair("G705F", 661));

    initVec.append(qMakePair("A601F", 78));
    initVec.append(qMakePair("A602F", 78));
    initVec.append(qMakePair("A603F", 78));
    initVec.append(qMakePair("A604F", 78));
    initVec.append(qMakePair("A605F", 78));
    initVec.append(qMakePair("A606F", 78));
    initVec.append(qMakePair("A607F", 78));
    initVec.append(qMakePair("A608F", 78));
    initVec.append(qMakePair("A609F", 78));
    initVec.append(qMakePair("A610F", 78));
    initVec.append(qMakePair("A611F", 78));
    initVec.append(qMakePair("A612F", 78));
    initVec.append(qMakePair("A613F", 78));
    initVec.append(qMakePair("A614F", 78));
    initVec.append(qMakePair("A615F", 78));
    initVec.append(qMakePair("A616F", 78));

    initVec.append(qMakePair("A001S", 620));
    initVec.append(qMakePair("A002S", 620));
    initVec.append(qMakePair("A003S", 620));
    initVec.append(qMakePair("A004S", 620));
    initVec.append(qMakePair("A001Q", 620));

    initVec.append(qMakePair("A102S", 930));

    initVec.append(qMakePair("I601S", 48));
    initVec.append(qMakePair("I602S", 48));
    initVec.append(qMakePair("I603S", 48));
    initVec.append(qMakePair("I604S", 48));
    initVec.append(qMakePair("I601Q", 48));

    initVec.append(qMakePair("I701S", 197));
    initVec.append(qMakePair("I702S", 197));
    initVec.append(qMakePair("I703S", 197));
    initVec.append(qMakePair("I704S", 197));
    initVec.append(qMakePair("I701Q", 197));

    initVec.append(qMakePair("A001F", 34));
    initVec.append(qMakePair("A002F", 34));
    initVec.append(qMakePair("A003F", 34));
    initVec.append(qMakePair("A004F", 34));
    initVec.append(qMakePair("A005F", 34));
    initVec.append(qMakePair("A006F", 34));
    initVec.append(qMakePair("A007F", 34));
    initVec.append(qMakePair("A008F", 34));
    initVec.append(qMakePair("A009F", 34));
    initVec.append(qMakePair("A010F", 34));
    initVec.append(qMakePair("A011F", 34));
    initVec.append(qMakePair("A012F", 34));
    initVec.append(qMakePair("A013F", 34));
    initVec.append(qMakePair("A014F", 34));
    initVec.append(qMakePair("A015F", 34));
    initVec.append(qMakePair("A016F", 34));

    initVec.append(qMakePair("H404F", 156));
    initVec.append(qMakePair("H405F", 156));

    initVec.append(qMakePair("B901S", 414));
    initVec.append(qMakePair("B902S", 414));
    initVec.append(qMakePair("B903S", 414));
    initVec.append(qMakePair("B904S", 414));
    initVec.append(qMakePair("B901Q", 414));

    trInfo_st initTrInfo;
    for(auto&& elemVec : initVec)
    {
        initTrInfo.n2Length = elemVec.second;
        mReqTrMap.insert(elemVec.first, initTrInfo);
    }

    //QMap데이터 확인
    /*QMapIterator<QString, trInfo_st> iter(mReqTrMap);
    while (iter.hasNext())
    {
        iter.next();
        qDebug() << iter.key() << " " << iter.value().n2Length;
    }
    */

    mpTimer = std::make_unique<QTimer>();
    QObject::connect(mpTimer.get(), SIGNAL(timeout()), this, SLOT(slotPrtStatsCycle()));
    // 1초 타이머
    mpTimer->start(1000);
}

CThDataReader::~CThDataReader()
{

}

void CThDataReader::slotPrtStatsCycle()
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

    mFile.setFileName(strFile);
    if(mFile.open(QIODevice::ReadOnly | QIODevice::Text) == false)
    {
        qDebug() << "Failed to open " << strFile << " file";
        return;
    }
    mTextStream.setDevice(&mFile);
    mTextStream.setEncoding(QStringConverter::System);

    // 파일을 불러온 후, 제대로 된 시세파일인지 여부를 검사.
    checkValidFile();
}

void CThDataReader::checkValidFile()
{
    QString sReadLine, sTrText, sTrCode;
    while (true)
    {
        if (mTextStream.atEnd() == false)
        {
            sReadLine = mTextStream.readLine();

            // epoch time이 마이크로 단위라 16자리
            // 따라서 읽은 Line이 16자리 이상이고 그다음 콜론(:)이 온다면 유효한 TR로 간주
            if (sReadLine.length() >= mCOLON_POS && sReadLine.at(mCOLON_POS) == ':')
            {
                sTrText = sReadLine.mid(mCOLON_POS + 1);
                sTrCode = sTrText.left(mTR_CODE_LEN);

                if (mReqTrMap.contains(sTrCode))
                {
                    emit sigValidFile();
                    break;
                }
            }
        }
    }
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

            // epoch time이 마이크로 단위라 16자리
            // 따라서 읽은 Line이 16자리 이상이고 그다음 콜론(:)이 온다면 유효한 TR로 간주
            if (sReadLine.length() >= mCOLON_POS && sReadLine.at(mCOLON_POS) == ':')
            {
                sTrText = sReadLine.mid(mCOLON_POS + 1);
                sTrCode = sTrText.left(mTR_CODE_LEN);

                // 버릴 수 없는 TR목록에 포함되면 처리
                if (mReqTrMap.contains(sTrCode))
                {
                    // 한글자리수 계산을 위해 ByteArr 사용
                    tmpByteArr = sTrText.toLocal8Bit();

                    // escape character까지 합한 값을 비교
                    if (tmpByteArr.length() + 1 == mReqTrMap[sTrCode].n2Length)
                    {
                        emit sigAnalyseData(sTrCode);
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                qDebug() << sReadLine;
            }
        }
        else
        {
            if (mFile.isOpen() == true)
            {
                mFile.close();
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
