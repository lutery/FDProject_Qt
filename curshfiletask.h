#ifndef CURSHFILETASK_H
#define CURSHFILETASK_H

#include "fdtask.h"

class CurshFileTask : public FDTask
{
public:
    explicit CurshFileTask(QString filePath, QObject* parent = nullptr);
    virtual ~CurshFileTask();

public slots:
    void execTask() override;

private:
    QString mFilePath;
};

#endif // CURSHFILETASK_H
