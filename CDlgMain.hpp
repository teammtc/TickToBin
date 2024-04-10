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
    int16_t mLength;
};

class CDlgMain : public QMainWindow
{
    Q_OBJECT

public:
    CDlgMain(QWidget *parent = nullptr);
    ~CDlgMain();
    void readNextLine(void);

    constexpr static size_t mCOLON_POS  = 16;
    constexpr static size_t mTR_CODE_LEN = 5;

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
