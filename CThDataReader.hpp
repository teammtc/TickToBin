#ifndef CTHDATAREADER_HPP
#define CTHDATAREADER_HPP

#include <QThread>
#include <QFile>
#include <QTextStream>

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
    std::unique_ptr<QFile> mpFile;
    QTextStream mTextStream;
    ThStatus mStatus = ThStatus::Init;
    ThStatus getStatus();
    void setStatus(ThStatus);
    void processReading();

private slots:
    void slotPrepareFile(QFile*);

public:
    CThDataReader();
    ~CThDataReader();

protected:
    void run();
};

#endif // CTHDATAREADER_HPP
