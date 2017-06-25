#include "fdservice.h"
//#include "analysisthread.h"
//#include "unlockthread.h"
//#include "deletethread.h"
//#include "curshfilethread.h"
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

void FDService::sltAnalysis(QString filePath)
{
   qDebug() << "FDService analysis";
//   stopThread(this->mpAnalysis);

//   this->mpAnalysis = new AnalysisThread(filePath);
//   connect((this->mpAnalysis), SIGNAL(onComplete(bool,QStringList)), this, SLOT(analysisComplete(bool,QStringList)));
//   this->mpAnalysis->start();

   AnalysisTask* pAnalysis = new AnalysisTask(filePath);
   connect(pAnalysis, SIGNAL(sigComplete(bool,QStringList)), this, SLOT(sltAnaComplete(bool,QStringList)));
   this->mpTaskCenter->pushTask(std::shared_ptr<AnalysisTask>(pAnalysis));
}

void FDService::sltUnlockHandle(QString filePath)
{
//    stopThread(this->mpUnlock);

//    this->mpUnlock = new UnlockThread(filePath);
//    connect((this->mpUnlock), SIGNAL(onUnlock(bool)), this, SIGNAL(unlock(bool)));
//    this->mpUnlock->start();
    std::shared_ptr<UnlockTask> pUnlockTask = std::shared_ptr<UnlockTask>(new UnlockTask(filePath));
    connect(pUnlockTask.get(), SIGNAL(sigUnlook(bool)), this, SIGNAL(unlock(bool)));
    this->mpTaskCenter->pushTask(pUnlockTask);
}

void FDService::sltDeleteFile(QString filePath)
{
    qDebug() << "FDService delete file start";
//    stopThread(this->mpTDelete);

//    this->mpTDelete = new DeleteThread(filePath);
//    connect((this->mpTDelete), SIGNAL(onDelFile(bool)), this, SIGNAL(delcomplete(bool)));
//    this->mpTDelete->start();
    std::shared_ptr<DeleteTask> pDeleteTask = std::shared_ptr<DeleteTask>(new DeleteTask(filePath));
    connect(pDeleteTask.get(), SIGNAL(sigDelFile(bool)), this, SIGNAL(delcomplete(bool)));
    this->mpTaskCenter->pushTask(pDeleteTask);
}

void FDService::sltCurshFile(QString filePath)
{
    qDebug() << "FDService curshFile start";
//    stopThread(this->mpTCursh);

//    this->mpTCursh = new CurshFileThread(filePath);
//    connect(this->mpTCursh, SIGNAL(onCurshFile(bool)), this, SIGNAL(crush(bool)));
//    this->mpTCursh->start();
    std::shared_ptr<CurshFileTask> pCurshFileTask = std::shared_ptr<CurshFileTask>(new CurshFileTask(filePath));
    connect(pCurshFileTask.get(), SIGNAL(sigCurshFile(bool)), this, SIGNAL(crush(bool)));
    this->mpTaskCenter->pushTask(pCurshFileTask);
}

void FDService::sltAnaComplete(bool isReady, QStringList filePaths)
{
    qDebug() << "isReady:" << (isReady ? "true" : "false");

    for (QString filePath : filePaths)
    {
        qDebug() << "filePath is " << filePath;
    }

    emit complete(filePaths);
}
