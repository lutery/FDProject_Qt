#ifndef ANALYSISTHREAD_H
#define ANALYSISTHREAD_H

#include <QThread>

/**
 * @brief The AnalysisThread class 分析线程，用于分析文件的占用信息
 */
class AnalysisThread : public QThread
{
    Q_OBJECT
public:
    explicit AnalysisThread(QString filePath, QObject *parent = 0);

signals:
    // 分析完成消息
    void onComplete(bool, QStringList);

public slots:


protected:
    void run() override;

private:
    // 需要分析文件的路径
    QString mFilePath;
};

#endif // ANALYSISTHREAD_H
