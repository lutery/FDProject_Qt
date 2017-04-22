#ifndef FDSERVICE_H
#define FDSERVICE_H

#include <QObject>

class FDObject;
class AnalysisThread;
class UnlockThread;

class FDService : public QObject
{
    Q_OBJECT
public:
    explicit FDService(QObject *parent = 0);
    ~FDService();

signals:
    void complete(QStringList filePaths);

public slots:
    void analysis(QString filePath);
    void unlockHandle(QString filePath);
    void analysisComplete(bool isReady, QStringList filePaths);

private:
    FDObject* mpFDObject;
    AnalysisThread* mpAnalysis;
    UnlockThread* mpUnlock;
};

#endif // FDSERVICE_H
