#include "analysistask.h"
#include "fdobject.h"

AnalysisTask::AnalysisTask(QString filePath, QObject *parent):FDTask(parent)
{
    this->mFilePath = filePath;
}

AnalysisTask::~AnalysisTask()
{

}

void AnalysisTask::execTask()
{
    FDObject fdObject;
    QObject::connect(&fdObject, SIGNAL(sigAnaComplet(bool,QStringList)), this, SIGNAL(sigComplete(bool,QStringList)));
    fdObject.sltAnalysis(mFilePath);
}
