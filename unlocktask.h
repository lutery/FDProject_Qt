#ifndef UNLOCKTASK_H
#define UNLOCKTASK_H

#include "fdtask.h"

class UnlockTask : public FDTask
{
public:
    explicit UnlockTask(QString filePath, QObject* parent = nullptr);
    virtual ~UnlockTask();

public slots:
    void execTask() override;

private:
    QString mFilePath;
};

#endif // UNLOCKTASK_H
