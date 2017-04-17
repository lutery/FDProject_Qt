#ifndef FDSERVICE_H
#define FDSERVICE_H

#include <QObject>

class FDObject;
class QThread;

class FDService : public QObject
{
    Q_OBJECT
public:
    explicit FDService(QObject *parent = 0);
    ~FDService();

signals:

public slots:
    void analysis(QString filePath);

private:
    FDObject* mpFDObject;
    QThread* mpAnalysis;
};

#endif // FDSERVICE_H
