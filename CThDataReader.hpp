#ifndef CTHDATAREADER_HPP
#define CTHDATAREADER_HPP

#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include "TrInterface.hpp"

enum class ThStatus
{
    Init = 0,
    Running,
    Stopped
};

class CThDataReader : public QThread
{
    Q_OBJECT

private:
    QFile mFile;
    QTextStream mTextStream;
    ThStatus mStatus = ThStatus::Init;
    ThStatus getStatus();
    void setStatus(ThStatus);
    void processReading();
    constexpr static qsizetype mCOLON_POS  = 16;
    constexpr static qsizetype mTR_CODE_LEN = 5;
    void checkValidFile();

signals:
    void sigValidFile();
    void sigAnalyseData(QString);

private slots:
    void slotPrepareFile(QString);

public:
    CThDataReader();
    ~CThDataReader();

    QMap<QString, trInterface> tR_CODE_SIZE() const;

protected:
    void run();
};

#endif // CTHDATAREADER_HPP
