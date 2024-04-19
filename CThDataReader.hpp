#ifndef CTHDATAREADER_HPP
#define CTHDATAREADER_HPP

#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QMap>

enum class ThStatus
{
    Init = 0,
    Running,
    Stopped
};

typedef struct strctInterface {
    QString interfaceNameKr;
    qint16 size;
} trInterface;

const trInterface IFMSRPD0002 {"증권 우선호가 (MM/LP호가 제외)", 555};
const trInterface IFMSRPD0003 {"증권 우선호가 (MM/LP호가 포함)", 795};
const trInterface IFMSRPD0004 {"증권 체결", 186};
const trInterface IFMSRPD0006 {"증권 체결 + 우선호가 (MM/LP호가 제외)", 648};
const trInterface IFMSRPD0007 {"증권 체결 + 우선호가 (MM/LP호가 포함)", 888};
const trInterface IFMSRPD0008 {"장운영TS", 68};
const trInterface IFMSRPD0034 {"파생 우선호가 (우선호가 5단계)", 315};
const trInterface IFMSRPD0035 {"파생 우선호가 (우선호가 10단계)", 545};
const trInterface IFMSRPD0036 {"파생 우선호가 (우선호가 5단계)", 173};
const trInterface IFMSRPD0037 {"파생 체결 + 우선호가 (우선호가 5단계)", 431};
const trInterface IFMSRPD0038 {"파생 체결 + 우선호가 (우선호가 10단계)", 661};
const trInterface IFMSRPD0041 {"파생 종목마감", 78};
const trInterface IFMSBTD0001 {"증권 종목정보", 620};
const trInterface IFMSBTD0004 {"ELW 종목정보", 930};
const trInterface IFMSBTD0010 {"종목이벤트 정보", 48};
const trInterface IFMSBTD0011 {"MM/LP 정보", 197};
const trInterface IFMSBTD0022 {"파생 종목정보", 1318};
const trInterface IFMSBTD0025 {"주식파생 조정내역", 156};
const trInterface IFMSSTD0006 {"거래상위 5개 회원 통계", 414};

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
    constexpr static qsizetype mCOLON_POS  = 16;
    constexpr static qsizetype mTR_CODE_LEN = 5;
    void checkValidFile();

    // 버릴 수 없는 TR 목록 및 각 TR의 사이즈
    const QMap<QString, strctInterface> mTR_CODE_SIZE {
        {"B601S", IFMSRPD0002}, {"B601Q", IFMSRPD0002}, {"B702S", IFMSRPD0003}, {"B703S", IFMSRPD0003}, {"B704S", IFMSRPD0003},
        {"A301S", IFMSRPD0004}, {"A302S", IFMSRPD0004}, {"A303S", IFMSRPD0004}, {"A304S", IFMSRPD0004}, {"A301Q", IFMSRPD0004},
        {"G701S", IFMSRPD0006}, {"G701Q", IFMSRPD0006}, {"G702S", IFMSRPD0007}, {"G703S", IFMSRPD0007}, {"G704S", IFMSRPD0007},
        {"A701S", IFMSRPD0008}, {"A702S", IFMSRPD0008}, {"A703S", IFMSRPD0008}, {"A704S", IFMSRPD0008}, {"A701Q", IFMSRPD0008},
        {"A701F", IFMSRPD0008}, {"A702F", IFMSRPD0008}, {"A703F", IFMSRPD0008}, {"A704F", IFMSRPD0008}, {"A705F", IFMSRPD0008},
        {"A706F", IFMSRPD0008}, {"A707F", IFMSRPD0008}, {"A708F", IFMSRPD0008}, {"A709F", IFMSRPD0008}, {"A710F", IFMSRPD0008},
        {"A711F", IFMSRPD0008}, {"A712F", IFMSRPD0008}, {"A713F", IFMSRPD0008}, {"A714F", IFMSRPD0008}, {"A715F", IFMSRPD0008},
        {"A716F", IFMSRPD0008}, {"A701G", IFMSRPD0008}, {"A701E", IFMSRPD0008}, {"B601F", IFMSRPD0034}, {"B602F", IFMSRPD0034},
        {"B603F", IFMSRPD0034}, {"B604F", IFMSRPD0035}, {"B605F", IFMSRPD0035}, {"B606F", IFMSRPD0034}, {"B607F", IFMSRPD0034},
        {"B608F", IFMSRPD0034}, {"B609F", IFMSRPD0034}, {"B610F", IFMSRPD0034}, {"B611F", IFMSRPD0034}, {"B612F", IFMSRPD0034},
        {"B613F", IFMSRPD0034}, {"B614F", IFMSRPD0034}, {"B615F", IFMSRPD0034}, {"B616F", IFMSRPD0034}, {"A301F", IFMSRPD0036},
        {"A302F", IFMSRPD0036}, {"A303F", IFMSRPD0036}, {"B615F", IFMSRPD0034}, {"A305F", IFMSRPD0036}, {"A306F", IFMSRPD0036},
        {"A307F", IFMSRPD0036}, {"A308F", IFMSRPD0036}, {"A309F", IFMSRPD0036}, {"A310F", IFMSRPD0036}, {"A311F", IFMSRPD0036},
        {"A312F", IFMSRPD0036}, {"A313F", IFMSRPD0036}, {"A314F", IFMSRPD0036}, {"A315F", IFMSRPD0036}, {"A316F", IFMSRPD0036},
        {"G701F", IFMSRPD0037}, {"G702F", IFMSRPD0037}, {"G703F", IFMSRPD0037}, {"G704F", IFMSRPD0038}, {"G705F", IFMSRPD0038},
        {"G706F", IFMSRPD0037}, {"G707F", IFMSRPD0037}, {"G708F", IFMSRPD0037}, {"G709F", IFMSRPD0037}, {"G710F", IFMSRPD0037},
        {"G711F", IFMSRPD0037}, {"G712F", IFMSRPD0037}, {"G713F", IFMSRPD0037}, {"G714F", IFMSRPD0037}, {"G715F", IFMSRPD0037},
        {"G716F", IFMSRPD0037}, {"A601F", IFMSRPD0041}, {"A602F", IFMSRPD0041}, {"A603F", IFMSRPD0041}, {"A604F", IFMSRPD0041},
        {"A605F", IFMSRPD0041}, {"A606F", IFMSRPD0041}, {"A607F", IFMSRPD0041}, {"A608F", IFMSRPD0041}, {"A609F", IFMSRPD0041},
        {"A610F", IFMSRPD0041}, {"A611F", IFMSRPD0041}, {"A612F", IFMSRPD0041}, {"A613F", IFMSRPD0041}, {"A614F", IFMSRPD0041},
        {"A615F", IFMSRPD0041}, {"A616F", IFMSRPD0041}, {"A001S", IFMSBTD0001}, {"A002S", IFMSBTD0001}, {"A003S", IFMSBTD0001},
        {"A004S", IFMSBTD0001}, {"A001Q", IFMSBTD0001}, {"A102S", IFMSBTD0004}, {"I601S", IFMSBTD0010}, {"I602S", IFMSBTD0010},
        {"I603S", IFMSBTD0010}, {"I604S", IFMSBTD0010}, {"I601Q", IFMSBTD0010}, {"I701S", IFMSBTD0011}, {"I702S", IFMSBTD0011},
        {"I703S", IFMSBTD0011}, {"I704S", IFMSBTD0011}, {"I701Q", IFMSBTD0011}, {"A001F", IFMSBTD0022}, {"A002F", IFMSBTD0022},
        {"A003F", IFMSBTD0022}, {"A004F", IFMSBTD0022}, {"A005F", IFMSBTD0022}, {"A006F", IFMSBTD0022}, {"A007F", IFMSBTD0022},
        {"A008F", IFMSBTD0022}, {"A009F", IFMSBTD0022}, {"A010F", IFMSBTD0022}, {"A011F", IFMSBTD0022}, {"A012F", IFMSBTD0022},
        {"A013F", IFMSBTD0022}, {"A014F", IFMSBTD0022}, {"A015F", IFMSBTD0022}, {"A016F", IFMSBTD0022}, {"H404F", IFMSBTD0025},
        {"H405F", IFMSBTD0025}, {"B901S", IFMSSTD0006}, {"B902S", IFMSSTD0006}, {"B903S", IFMSSTD0006}, {"B904S", IFMSSTD0006},
        {"B901Q", IFMSSTD0006}
    };

signals:
    void sigValidFile();

private slots:
    void slotPrepareFile(QString);

public:
    CThDataReader();
    ~CThDataReader();

    QMap<QString, strctInterface> tR_CODE_SIZE() const;

protected:
    void run();
};

#endif // CTHDATAREADER_HPP
