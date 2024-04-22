#include "CDlgMain.hpp"
#include "ui_CDlgMain.h"
#include "TrInterface.hpp"

CDlgMain::CDlgMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CDlgMain)
{
    ui->setupUi(this);

    QString iStr2 = "v0.01 <2024.04.10(01)>";

#if DEBUG
    this->setWindowTitle("TickToBin (DEBUG Mode) " + iStr2);
#elif RELEASE
    this->setWindowTitle("TickToBin " + iStr2);
#endif

    mpThDataReader = std::make_unique<CThDataReader>();

    // CDlgMain의 sigPrepareFile이 호출되면 CThDataReader의 slotPrepareFile에서 받는다.
    QObject::connect(this, SIGNAL(sigPrepareFile(QString)), mpThDataReader.get(), SLOT(slotPrepareFile(QString)), Qt::QueuedConnection);

    // CThDataReader에서 sigValidFile을 내보내면 CDlgMain에서 slotValidFile을 통해 받는다.
    QObject::connect(mpThDataReader.get(), SIGNAL(sigValidFile()), this, SLOT(slotValidFile()), Qt::QueuedConnection);

    // CThDataReader에서 sigAnalyseData를 내보내면 CDlgMain에서 slotAnalyseData를 통해 받는다.
    QObject::connect(mpThDataReader.get(), SIGNAL(sigAnalyseData(QString)), this, SLOT(slotAnalyseData(QString)), Qt::QueuedConnection);
}

CDlgMain::~CDlgMain()
{
    delete ui;
    mpThDataReader->quit();
    mpThDataReader->wait();
}

void CDlgMain::slotBtnOpenFile(void)
{
    QString sFileName = QFileDialog::getOpenFileName(nullptr
                                                     , tr("Open File")
                                                     , QDir::homePath()
                                                     , tr("Text files (*.txt)"));

    emit sigPrepareFile(sFileName);
}

void CDlgMain::slotBtnNextTR(void)
{
    mpThDataReader->start();
}

void CDlgMain::slotBtnStatsTR(void)
{
    // 버튼이 활성화 된 상태인지 한번 더 확인
    if(ui->btnStatsTR->isEnabled())
    {
        qDebug() << "clicked btnStatsTR.";
        ui->btnStatsTR->setEnabled(false);
    }
}

void CDlgMain::slotValidFile()
{
    qDebug() << "valid file.";
    ui->btnStatsTR->setEnabled(true);
}

void CDlgMain::slotAnalyseData(QString trCode)
{
    auto& data = mapTrCode[trCode];
    data.occurrence += 1;


    for(auto [key, data] : mapTrCode.asKeyValueRange())
    {
        qDebug() << key << data.occurrence;
    }
}
