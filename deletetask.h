#ifndef DELETETASK_H
#define DELETETASK_H

#include "fdtask.h"

class DeleteTask : public FDTask
{
public:
    explicit DeleteTask(QString filePath, QObject* parent = nullptr);
    virtual ~DeleteTask();

public slots:
    void execTask() override;

private:
    QString mFilePath;
};

#endif // DELETETASK_H
