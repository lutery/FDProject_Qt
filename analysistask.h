#ifndef ANALYSISTASK_H
#define ANALYSISTASK_H

#include "fdtask.h"

/**
 * @brief The AnalysisTask class 解析任务
 */
class AnalysisTask : public FDTask
{
    Q_OBJECT
public:
    explicit AnalysisTask(QString filePath, QObject* parent = nullptr);
    virtual ~AnalysisTask();

signals:
    // 任务执行完毕信号
    void sigComplete(bool, QStringList);

public slots:
    void execTask() override;

private:
    // 需要分析文件的路径
    QString mFilePath;
};

#endif // ANALYSISTASK_H
