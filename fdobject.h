#ifndef FDOBJECT_H
#define FDOBJECT_H

#include <QObject>
#include <QString>
#include <QVector>
#include <memory>
#include "predefine.h"

class FDObject : public QObject
{
    Q_OBJECT
public:
    explicit FDObject(QObject *parent = 0);
    ~FDObject();

signals:
    void analysisComplete(bool isReady, QVector<std::shared_ptr<ncFileHandle>>);

public slots:

private:
    bool mbAnalyse;
    QVector<std::shared_ptr<ncFileHandle>> mHandles;

public:
    void analysis(QString filePath);
};

#endif // FDOBJECT_H
