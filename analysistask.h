#ifndef ANALYSISTASK_H
#define ANALYSISTASK_H

#include "fdtask.h"

class AnalysisTask : public FDTask
{
    Q_OBJECT
public:
    explicit AnalysisTask(QString filePath, QObject* parent = nullptr);
    virtual ~AnalysisTask();

signals:
    void sigComplete(bool, QStringList);

public slots:
    void execTask() override;

private:
    // 需要分析文件的路径
    QString mFilePath;
};

#endif // ANALYSISTASK_H
