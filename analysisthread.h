#ifndef ANALYSISTHREAD_H
#define ANALYSISTHREAD_H

#include <QThread>

class AnalysisThread : public QThread
{
    Q_OBJECT
public:
    explicit AnalysisThread(QString filePath, QObject *parent = 0);

signals:
    void onComplete(bool, QStringList);

public slots:


protected:
    void run() override;

private:
    QString mFilePath;
};

#endif // ANALYSISTHREAD_H
