#include "fdservice.h"
#include "analysisthread.h"
#include "unlockthread.h"
#include "deletethread.h"
#include "curshfilethread.h"
#include "taskcenter.h"
#include "analysistask.h"
#include "unlocktask.h"
#include "deletetask.h"
#include "curshfiletask.h"
#include <fdobject.h>
#include <QDebug>

FDService::FDService(QObject *parent) : QObject(parent)
{
//    this->mpFDObject = nullptr;
//    this->mpFDObject = new FDObject();
//    this->mpAnalysis = nullptr;
//    this->mpUnlock = nullptr;
//    this->mpTDelete = nullptr;
//    this->mpTCursh = nullptr;
    this->mpTaskCenter = new TaskCenter();
    this->mpTaskCenter->start();
}

FDService::~FDService()
{
//    if (this->mpFDObject != nullptr)
//    {
//        delete this->mpFDObject;
//        this->mpFDObject = nullptr;
//    }

//    stopThread(this->mpAnalysis);
//    stopThread(this->mpUnlock);
//    stopThread(this->mpTDelete);
//    stopThread(this->mpTCursh);
    stopThread(this->mpTaskCenter);
}

void FDService::analysis(QString filePath)
{
   qDebug() << "FDService analysis";
//   stopThread(this->mpAnalysis);

//   this->mpAnalysis = new AnalysisThread(filePath);
//   connect((this->mpAnalysis), SIGNAL(onComplete(bool,QStringList)), this, SLOT(analysisComplete(bool,QStringList)));
//   this->mpAnalysis->start();

   std::shared_ptr<AnalysisTask> pAnalysis = std::shared_ptr<AnalysisTask>(new AnalysisTask(filePath));
   this->mpTaskCenter->pushTask(pAnalysis);
}

void FDService::unlockHandle(QString filePath)
{
//    stopThread(this->mpUnlock);

//    this->mpUnlock = new UnlockThread(filePath);
//    connect((this->mpUnlock), SIGNAL(onUnlock(bool)), this, SIGNAL(unlock(bool)));
//    this->mpUnlock->start();
    std::shared_ptr<UnlockTask> pUnlockTask = std::shared_ptr<UnlockTask>(new UnlockTask(filePath));
    this->mpTaskCenter->pushTask(pUnlockTask);
}

void FDService::deleteFile(QString filePath)
{
    qDebug() << "FDService delete file start";
//    stopThread(this->mpTDelete);

//    this->mpTDelete = new DeleteThread(filePath);
//    connect((this->mpTDelete), SIGNAL(onDelFile(bool)), this, SIGNAL(delcomplete(bool)));
//    this->mpTDelete->start();
    std::shared_ptr<DeleteTask> pDeleteTask = std::shared_ptr<DeleteTask>(new DeleteTask(filePath));
    this->mpTaskCenter->pushTask(pDeleteTask);
}

void FDService::curshFile(QString filePath)
{
    qDebug() << "FDService curshFile start";
//    stopThread(this->mpTCursh);

//    this->mpTCursh = new CurshFileThread(filePath);
//    connect(this->mpTCursh, SIGNAL(onCurshFile(bool)), this, SIGNAL(crush(bool)));
//    this->mpTCursh->start();
    std::shared_ptr<CurshFileTask> pCurshFileTask = std::shared_ptr<CurshFileTask>(new CurshFileTask(filePath));
    this->mpTaskCenter->pushTask(pCurshFileTask);
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
