#ifndef CDLGMAIN_HPP
#define CDLGMAIN_HPP

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui {
class CDlgMain;
}
QT_END_NAMESPACE

struct trInfo_ST
{
    int mCnt;
    int mLength;

    trInfo_ST()
    {
        mCnt    = 0;
        mLength = 0;
    }
};

class CDlgMain : public QMainWindow
{
    Q_OBJECT

public:
    CDlgMain(QWidget *parent = nullptr);
    ~CDlgMain();
    void readNextLine(void);

    constexpr static int8_t mColonPos = 16;

private:
    Ui::CDlgMain *ui;
    QFile         mFile;
    QTextStream   mTextStream;

    QMap<QString, trInfo_ST> mReqTrMap;

private slots:
    void slotBtnOpenFile(void);
    void slotBtnNextTR(void);
};
#endif // CDLGMAIN_HPP
