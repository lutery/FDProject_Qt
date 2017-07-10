#include "analysistask.h"
#include "fdobject.h"
#include <QDebug>

AnalysisTask::AnalysisTask(QString filePath, QObject *parent):FDTask(parent)
{
    this->mFilePath = filePath;
}

AnalysisTask::~AnalysisTask()
{

}
/**
 * @brief AnalysisTask::execTask 执行任务函数
 */
void AnalysisTask::execTask()
{
    // 创建文件管理对象
    FDObject fdObject;
    // 连接fdObject分析完成信号以及自身的完成信号
    QObject::connect(&fdObject, SIGNAL(sigAnaComplet(bool,QStringList)), this, SIGNAL(sigComplete(bool,QStringList)));
    qDebug() << "start Analysis";
    // 文件管理对象解析函数槽
    fdObject.sltAnalysis(mFilePath);
    qDebug() << "end Analysis";
}
