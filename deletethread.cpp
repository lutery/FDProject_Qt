#include "deletethread.h"
#include "fdobject.h"
#include <QDebug>

DeleteThread::DeleteThread(QString filePath, QObject *parent) : QThread(parent)
{
    this->mFilePath = filePath;
}

void DeleteThread::run()
{
    FDObject fdObject;
    QObject::connect(&fdObject, SIGNAL(onDelFile(bool)), this, SIGNAL(onDelFile(bool)));
    qDebug() << "start delete file";
    fdObject.deleteFile(mFilePath);
    qDebug() << "end delete file";
}
