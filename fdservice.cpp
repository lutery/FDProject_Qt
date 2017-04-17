#include "fdservice.h"
#include <fdobject.h>
#include <QThread>

//class AnalysisThread : public QThread
//{
//protected:
//    void run() override
//    {

//    }
//};

FDService::FDService(QObject *parent) : QObject(parent)
{
    this->mpFDObject = nullptr;
    this->mpFDObject = new FDObject();
}

FDService::~FDService()
{
    if (this->mpFDObject != nullptr)
    {
        delete this->mpFDObject;
        this->mpFDObject = nullptr;
    }
}

void FDService::analysis(QString filePath)
{

}
