#ifndef HttpRequestFile_hpp
#define HttpRequestFile_hpp

#include <QObject>
#include <QtNetwork>
#include <QFile>

class HttpRequest : public QObject
{
        Q_OBJECT

public:
        HttpRequest(QUrl url, bool saveToFile = true);
	void wait();

public slots:
	void start();

protected slots:
        void startRequest();
        void httpReadyRead();
        void cancelDownload();
        void httpFinished();
        void updateDataReadProgress(qint64 bytesRead, qint64 totalBytes);

signals:
        void progressValueChanged(int progress);
        void progressRangeChanged(int lowerLimit, int upperLimit);
        void downloadComplete(QString /* fileName or data */);
        void downloadComplete();

private:
        QUrl url;
        QFile *file;
        QString *data;
        QNetworkAccessManager *qnam;
        QNetworkReply *reply;
        bool saveToFile;
        bool httpRequestAborted;
	bool httpRequestComplete;
        int httpGetId;
};

#endif /* HttpRequestFile_hpp */
