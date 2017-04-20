#ifndef FDSERVICE_H
#define FDSERVICE_H

#include <QObject>

class FDObject;
class AnalysisThread;

class FDService : public QObject
{
    Q_OBJECT
public:
    explicit FDService(QObject *parent = 0);
    ~FDService();

signals:

public slots:
    void analysis(QString filePath);
    void analysisComplete(bool isReady, QStringList filePaths);

private:
    FDObject* mpFDObject;
    AnalysisThread* mpAnalysis;
};

#endif // FDSERVICE_H
