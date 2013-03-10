#include <cstdlib>
#include <iostream>

#include <QObject>
#include <QtNetwork>

#include "HttpRequest.hpp"

HttpRequest::HttpRequest(QUrl inputUrl, bool inputSaveToFile) :
        url(inputUrl),
        saveToFile(inputSaveToFile),
	httpRequestComplete(false)
{

}

void HttpRequest::start()
{
        qnam = new QNetworkAccessManager();

        if (saveToFile) {
                // Set File Name
                QFileInfo fileInfo(url.path());
                QString fileName = fileInfo.fileName();
                if (fileName.isEmpty())
                        fileName = "index.html";
                fileName = "download/" + fileName;

                // Check for Download Directory
                QDir dir("download/");
                if (!dir.exists())
                        dir.mkpath(".");

                // Check for Existing File
                if (QFile::exists(fileName))
                        QFile::remove(fileName);

                // Open File
                file = new QFile(fileName);
                if (!file->open(QIODevice::WriteOnly)) {
                        file->deleteLater();
                        qFatal("Permission denied to open download file. Please check permissions.");
                        exit(-1);
                }
        } else {
                data = new QString("");
        }

        // Run Download
        httpRequestAborted = false;
        startRequest();
}

void HttpRequest::wait()
{
	while (!httpRequestComplete);
}

void HttpRequest::startRequest()
{
        reply = qnam->get(QNetworkRequest(url));
        connect(reply, SIGNAL(finished()), this, SLOT(httpFinished()));
        connect(reply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));
        connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(updateDataReadProgress(qint64, qint64)));
}

void HttpRequest::cancelDownload()
{
        httpRequestAborted = true;
        reply->abort();
}

void HttpRequest::httpReadyRead()
{
        if (saveToFile)
                file->write(reply->readAll());
        else
                *data += QString(reply->readAll());
}

void HttpRequest::httpFinished()
{
        QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
        if (reply->error()) {
                qFatal("Network error");
                exit(-1);
        } else if (!redirectionTarget.isNull()) {
                url = url.resolved(redirectionTarget.toUrl());
                reply->deleteLater();
                startRequest();
                return;
        }

        reply->deleteLater();
        qnam->deleteLater();
        if (saveToFile) {
                emit downloadComplete(file->fileName());
                file->deleteLater();
        } else {
                emit downloadComplete(QString(*data));
                delete data;
        }

	httpRequestComplete = true;
        emit downloadComplete();
}

void HttpRequest::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
        emit progressRangeChanged(0, totalBytes);
        emit progressValueChanged(bytesRead);
}
