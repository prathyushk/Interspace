#include <cstdlib>

#include <QObject>
#include <QString>
#include <QFile>
#include <QDir>
#include <QUrl>

#include "HttpRequest.hpp"
#include "Updater.hpp"

Updater::Updater() :
	installedVersion(0),
	currentVersion(0)
{

}

void Updater::checkForUpdates()
{
	// Initialize
	checkForDataDir();
	getInstalledVersion();

	// Get New Version Number
	httpRequest = new HttpRequest(QUrl("http://interspacegame.com/update/version"), false);
	connect(httpRequest, SIGNAL(downloadComplete(QString)), this, SIGNAL(checkForNewVersion(QString)));
	httpRequest->start();
}

void Updater::checkForDataDir()
{
	QDir dir("data/");
	if (!dir.exists())
		dir.mkpath(".");	
}

void Updater::getInstalledVersion()
{
	QFile versionFile("data/version");
	if (!versionFile.exists()) {
		installedVersion = 0;
	} else {
		QTextStream versionFileStream(&versionFile);
		installedVersion = versionFileStream.readLine().toInt();
	}
	versionFile.close();
}

void Updater::checkForNewVersion(QString version)
{
	currentVersion = version.toInt();
	if (installedVersion < currentVersion)
		emit updateAvailable();
	else
		emit isUpToDate();

	httpRequest->disconnect();
	httpRequest->deleteLater();
}

void Updater::runUpdates()
{
	if (installedVersion == 0) {
#ifdef PLATFORM_LINUX
		httpRequest = new HttpRequest(QUrl("http://interspacegame.com/update/linux/interspace-" + QString::number(currentVersion) + ".tar.gz"));
#else
		httpRequest = new HttpRequest(QUrl("http://interspacegame.com/update/windows/interspace-" + QString::number(currentVersion) + ".zip"));
#endif
		connect(httpRequest, SIGNAL(progressValueChanged(int)), this, SIGNAL(progressValueChanged(int)));
		connect(httpRequest, SIGNAL(progressRangeChanged(int, int)), this, SIGNAL(progressRangeChanged(int, int)));
		connect(httpRequest, SIGNAL(downloadComplete(QString)), this, SLOT(installFirstVersion()));
		httpRequest->start();
		httpRequest->wait();
		httpRequest->disconnect();
		httpRequest->deleteLater();
		emit finishedUpdating();
		return;
	} else if (installedVersion == currentVersion) {
		emit finishedUpdating();
		return;
	}

	QDir binDir("bin");
	binDir.rename("interspace", "interspace-" + QString::number(installedVersion));

	for (; installedVersion < currentVersion; ++installedVersion) {
#ifdef PLATFORM_LINUX
		httpRequest = new HttpRequest(QUrl("http://interspacegame.com/update/linux/interspace-" + QString::number(installedVersion + 1) + ".patch.gz"));
#else
		httpRequest = new HttpRequest(QUrl("http://interspacegame.com/update/windows/interspace-" + QString::number(installedVersion + 1) + ".patch.zip"));
#endif
		connect(httpRequest, SIGNAL(progressValueChanged(int)), this, SIGNAL(progressValueChanged(int)));
		connect(httpRequest, SIGNAL(progressRangeChanged(int, int)), this, SIGNAL(progressRangeChanged(int, int)));
		connect(httpRequest, SIGNAL(downloadComplete(QString)), this, SLOT(applyPatch(QString)));
		httpRequest->start();
		httpRequest->wait();
		httpRequest->disconnect();
	        httpRequest->deleteLater();
		binDir.rename("interspace-" + QString::number(installedVersion), "interspace-" + QString::number(installedVersion + 1));
	}
	
	binDir.rename("interspace-" + QString::number(installedVersion), "interspace");
	
	QFile versionFile("data/version");
	if (!versionFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
		qFatal("I/O error");
		exit(-1);
	}
	QTextStream versionFileOut(&versionFile);
	versionFileOut << currentVersion;
	versionFile.close();

	emit finishedUpdating();
}

void Updater::applyPatch(QString fileName)
{
	QProcess *patchProcess = new QProcess();
	patchProcess->setWorkingDirectory("bin/interspace-" + QString::number(installedVersion));
	QString patchExecutable("/usr/bin/patch");
	QStringList patchArguments;
	patchArguments << "-p1" << "-i" << "../../" + fileName;
	patchProcess->start(patchExecutable, patchArguments);
	patchProcess->waitForFinished(-1);
	patchProcess->deleteLater();
}

void Updater::installFirstVersion(QString fileName)
{
	QProcess *installProcess = new QProcess();
	installProcess->setWorkingDirectory("bin");
	QString installExecutable("/bin/tar");
	QStringList installArguments;
	installArguments << "xzf" << "../../" + fileName;
	installProcess->start(installExecutable, installArguments);
	installProcess->waitForFinished(-1);
	installProcess->deleteLater();
}
