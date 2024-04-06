#ifndef CDLGMAIN_HPP
#define CDLGMAIN_HPP

#include <QMainWindow>
#include <QFile>

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

private:
    QFile mFile;
    QTextStream mTxtStream;
    const quint16 lenEpochTime = 16;

    // 버릴 수 없는 TR 목록
    const QVector<QString> TR_CODES {
        "B601S", "B601Q", "B702S", "B703S", "B704S",
        "A301S", "A302S", "A303S", "A304S", "A301Q",
        "G701S", "G701Q", "G702S", "G703S", "G704S",
        "A701S", "A702S", "A703S", "A704S", "A701Q",
        "A701F", "A702F", "A703F", "A704F", "A705F",
        "A706F", "A707F", "A708F", "A709F", "A710F",
        "A711F", "A712F", "A713F", "A714F", "A715F",
        "A716F", "A701G", "A701E", "B601F", "B602F",
        "B603F", "B604F", "B605F", "B606F", "B607F",
        "B608F", "B609F", "B610F", "B611F", "B612F",
        "B613F", "B614F", "B615F", "B616F", "A301F",
        "A302F", "A303F", "A304F", "A305F", "A306F",
        "A307F", "A308F", "A309F", "A310F", "A311F",
        "A312F", "A313F", "A314F", "A315F", "A316F",
        "G701F", "G702F", "G703F", "G704F", "G705F",
        "G706F", "G707F", "G708F", "G709F", "G710F",
        "G711F", "G712F", "G713F", "G714F", "G715F",
        "G716F", "A601F", "A602F", "A603F", "A604F",
        "A605F", "A606F", "A607F", "A608F", "A609F",
        "A610F", "A611F", "A612F", "A613F", "A614F",
        "A615F", "A616F", "A001S", "A002S", "A003S",
        "A004S", "A001Q", "A102S", "I601S", "I602S",
        "I603S", "I604S", "I601Q", "I701S", "I702S",
        "I703S", "I704S", "I701Q", "A001F", "A002F",
        "A003F", "A004F", "A005F", "A006F", "A007F",
        "A008F", "A009F", "A010F", "A011F", "A012F",
        "A013F", "A014F", "A015F", "A016F", "H404F",
        "H405F", "B901S", "B902S", "B903S", "B904S",
        "B901Q"
    };
};
#endif // CDLGMAIN_HPP
