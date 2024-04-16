#include "CThDataReader.hpp"
#include <QDebug>

CThDataReader::CThDataReader()
{

}

CThDataReader::~CThDataReader()
{

}

void CThDataReader::slotProcessFile(QFile* file)
{
    qDebug() << "slotProcessFile is called.";
}

void CThDataReader::run()
{
    qDebug() << "reading";
};
