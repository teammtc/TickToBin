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

class CDlgMain : public QMainWindow
{
    Q_OBJECT

public:
    CDlgMain(QWidget *parent = nullptr);
    ~CDlgMain();

private:
    Ui::CDlgMain *ui;

private slots:
    void slotBtnOpenFile(void);
    void slotBtnNextTR(void);
};
#endif // CDLGMAIN_HPP
