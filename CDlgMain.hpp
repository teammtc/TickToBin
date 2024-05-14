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

class CDlgMain : public QMainWindow
{
    Q_OBJECT

public:
    CDlgMain(QWidget *parent = nullptr);
    ~CDlgMain();

private:
    Ui::CDlgMain *ui;
    std::unique_ptr<CThDataReader> mpThDataReader;
    void displayMessage(QString);

signals:
    void sigPrepareFile(QString);

private slots:
    void slotBtnOpenFile(void);
    void slotBtnStatsTR(void);
    void slotFileValidity(bool);
    void slotAnalyseData(QString);
    void slotDisplayMessage(QString);
    void slotDisplayPercentage(int);
    void slotAnalysisDone();
};
#endif // CDLGMAIN_HPP
