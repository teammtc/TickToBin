#ifndef CDLGMAIN_HPP
#define CDLGMAIN_HPP

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "CThDataReader.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class CDlgMain;
}
QT_END_NAMESPACE

struct trInfo_st
{
    int64_t mCnt;
    int16_t mLength;
};

class CDlgMain : public QMainWindow
{
    Q_OBJECT

public:
    CDlgMain(QWidget *parent = nullptr);
    ~CDlgMain();
    void readNextLine(void);

    constexpr static qsizetype mCOLON_POS  = 16;
    constexpr static qsizetype mTR_CODE_LEN = 5;

private:
    Ui::CDlgMain *ui;
    std::unique_ptr<QFile> mpFile;
    QTextStream   mTextStream;

    QMap<QString, trInfo_st> mReqTrMap;
    std::unique_ptr<CThDataReader> mpThDataReader;

signals:
    void sigProcessFile(QFile*);

private slots:
    void slotBtnOpenFile(void);
    void slotBtnNextTR(void);
    void slotBtnStatsTR(void);

};
#endif // CDLGMAIN_HPP
