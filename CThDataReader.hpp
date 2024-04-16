#ifndef CTHDATAREADER_HPP
#define CTHDATAREADER_HPP

#include <QThread>
#include <QFile>

class CThDataReader : public QThread
{
    Q_OBJECT

private:
    QFile mFile;

private slots:
    void slotProcessFile(QFile*);

public:
    CThDataReader();
    ~CThDataReader();

protected:
    void run();
};

#endif // CTHDATAREADER_HPP
