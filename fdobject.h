#ifndef FDOBJECT_H
#define FDOBJECT_H

#include <QObject>
#include <QString>
#include <QVector>
#include <memory>
#include <QStringList>
#include "predefine.h"

class FDObject : public QObject
{
    Q_OBJECT
public:
    explicit FDObject(QObject *parent = 0);
    ~FDObject();

signals:
    void analysisComplete(bool, QVector<std::shared_ptr<ncFileHandle>>);
    void onComplete(bool, QStringList);

public slots:
    void analysis(QString filePath);

private:
    bool mbAnalyse;
    QVector<std::shared_ptr<ncFileHandle>> mHandles;

public:

};

#endif // FDOBJECT_H
