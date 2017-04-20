#include "fdservice.h"
#include "analysisthread.h"
#include <fdobject.h>
#include <QDebug>

FDService::FDService(QObject *parent) : QObject(parent)
{
    this->mpFDObject = nullptr;
    this->mpFDObject = new FDObject();
    this->mpAnalysis = nullptr;
}

FDService::~FDService()
{
    if (this->mpFDObject != nullptr)
    {
        delete this->mpFDObject;
        this->mpFDObject = nullptr;
    }

    if (this->mpAnalysis != nullptr)
    {
        this->mpAnalysis->quit();
        this->mpAnalysis->wait();
        delete this->mpAnalysis;
        this->mpAnalysis = nullptr;
    }
}

void FDService::analysis(QString filePath)
{
   qDebug() << "FDService analysis";
   if (this->mpAnalysis != nullptr)
   {
       return;
   }

   this->mpAnalysis = new AnalysisThread(filePath);
   connect((this->mpAnalysis), SIGNAL(onComplete(bool,QStringList)), this, SLOT(analysisComplete(bool,QStringList)));
   this->mpAnalysis->start();
}

void FDService::analysisComplete(bool isReady, QStringList filePaths)
{
    qDebug() << "isReady:" << (isReady ? "true" : "false");

    for (QString filePath : filePaths)
    {
        qDebug() << "filePath is " << filePath;
    }
}
