#include "fdservice.h"
#include "analysisthread.h"
#include "unlockthread.h"
#include "deletethread.h"
#include "curshfilethread.h"
#include <fdobject.h>
#include <QDebug>

FDService::FDService(QObject *parent) : QObject(parent)
{
    this->mpFDObject = nullptr;
    this->mpFDObject = new FDObject();
    this->mpAnalysis = nullptr;
    this->mpUnlock = nullptr;
    this->mpTDelete = nullptr;
    this->mpTCursh = nullptr;
}

FDService::~FDService()
{
    if (this->mpFDObject != nullptr)
    {
        delete this->mpFDObject;
        this->mpFDObject = nullptr;
    }

    stopThread(this->mpAnalysis);
    stopThread(this->mpUnlock);
    stopThread(this->mpTDelete);
    stopThread(this->mpTCursh);
}

void FDService::analysis(QString filePath)
{
   qDebug() << "FDService analysis";
   stopThread(this->mpAnalysis);

   this->mpAnalysis = new AnalysisThread(filePath);
   connect((this->mpAnalysis), SIGNAL(onComplete(bool,QStringList)), this, SLOT(analysisComplete(bool,QStringList)));
   this->mpAnalysis->start();
}

void FDService::unlockHandle(QString filePath)
{
    stopThread(this->mpUnlock);

    this->mpUnlock = new UnlockThread(filePath);
    connect((this->mpUnlock), SIGNAL(onUnlock(bool)), this, SIGNAL(unlock(bool)));
    this->mpUnlock->start();
}

void FDService::deleteFile(QString filePath)
{
    qDebug() << "FDService delete file start";
    stopThread(this->mpTDelete);

    this->mpTDelete = new DeleteThread(filePath);
    connect((this->mpTDelete), SIGNAL(onDelFile(bool)), this, SIGNAL(delcomplete(bool)));
    this->mpTDelete->start();
}

void FDService::curshFile(QString filePath)
{
    qDebug() << "FDService curshFile start";
    stopThread(this->mpTCursh);

    this->mpTCursh = new CurshFileThread(filePath);
    connect(this->mpTCursh, SIGNAL(onCurshFile(bool)), this, SIGNAL(crush(bool)));
    this->mpTCursh->start();
}

void FDService::analysisComplete(bool isReady, QStringList filePaths)
{
    qDebug() << "isReady:" << (isReady ? "true" : "false");

    for (QString filePath : filePaths)
    {
        qDebug() << "filePath is " << filePath;
    }

    emit complete(filePaths);
}
