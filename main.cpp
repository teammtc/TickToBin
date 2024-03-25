#include "CDlgMain.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::unique_ptr<CDlgMain> w = std::make_unique<CDlgMain>();

    w->show();

    return a.exec();
}
