#ifndef ANALYSISTASK_H
#define ANALYSISTASK_H

#include "fdtask.h"

class AnalysisTask : public FDTask
{
public:
    explicit AnalysisTask(QString filePath, QObject* parent = nullptr);

public slots:
    void execTask() override;

private:
    // 需要分析文件的路径
    QString mFilePath;
};

#endif // ANALYSISTASK_H
