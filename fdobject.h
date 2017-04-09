#ifndef FDOBJECT_H
#define FDOBJECT_H

#include <QObject>
#include <QString>
#include <QVector>
#include <memory>

struct ncFileHandle;

class FDObject : public QObject
{
    Q_OBJECT
public:
    explicit FDObject(QObject *parent = 0);
    ~FDObject();

signals:
    void analysisComplete(QVector<ncFileHandle>);

public slots:

private:
    QVector<std::shared_ptr<ncFileHandle>> mHandles;

public:
    void analysis(QString filePath);
};

#endif // FDOBJECT_H
