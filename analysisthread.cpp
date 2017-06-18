#include "analysisthread.h"
#include "fdobject.h"
#include <QDebug>

/**
 * @brief AnalysisThread::AnalysisThread
 * @param filePath 需要分析文件的路径
 * @param parent QObject父类对象
 */
AnalysisThread::AnalysisThread(QString filePath, QObject *parent) : QThread(parent)
{
    this->mFilePath = filePath;
}

/**
 * @brief AnalysisThread::run 子线程执行主体
 */
void AnalysisThread::run()
{
    FDObject fdObject;
    // 连接FDObject解析完成信号到分析线程解析完成信号，执行信号转发
    QObject::connect(&fdObject, SIGNAL(onComplete(bool,QStringList)), this, SIGNAL(onComplete(bool,QStringList)));
    qDebug() << "start run";
    fdObject.sltAnalysis(mFilePath);
    qDebug() << "end run";
}
