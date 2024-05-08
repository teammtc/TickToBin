#ifndef CTHDATAREADER_HPP
#define CTHDATAREADER_HPP

#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QTimer>

enum class ThStatus
{
    Init = 0,
    Running,
    Stopped
};

struct trInfo_st
{
    int64_t n1Cnt    = 0;
    int16_t n2Length = 0;
};

class CThDataReader : public QThread
{
    Q_OBJECT

private:
    QFile mFile;
    quint64 mFileSize = 0; // 전체 파일 사이즈를 담을 멤버변수
    quint64 mReadFileSize = 0; // 특정 시점까지 읽어들인 파일의 크기를 담을 멤버변수
    QTextStream mTextStream;
    ThStatus mStatus = ThStatus::Init;
    ThStatus getStatus();
    void setStatus(ThStatus);
    void processReading();
    constexpr static qsizetype mCOLON_POS  = 16;
    constexpr static qsizetype mTR_CODE_LEN = 5;
    void checkValidFile();
    std::unique_ptr<QTimer> mpTimer;

signals:
    void sigValidFile();
    void sigAnalyseData(QString);
    void sigDisplayMessage(QString);
    void sigDisplayPercentage(int);

private slots:
    void slotPrepareFile(QString);
    void slotPrtStatsCycle();

public:
    CThDataReader();
    ~CThDataReader();

    QMap<QString, trInfo_st> mReqTrMap;

protected:
    void run();
};

#endif // CTHDATAREADER_HPP
