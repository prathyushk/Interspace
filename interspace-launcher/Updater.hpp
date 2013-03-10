#ifndef Updater_hpp
#define Updater_hpp

#include <QObject>
#include <QString>

#include "HttpRequest.hpp"

class Updater : public QObject
{
	Q_OBJECT

public:
	Updater();

public slots:
	void checkForUpdates();
	void runUpdates();

private slots:
	void checkForNewVersion(QString version);
	void applyPatch(QString fileName);
	void installFirstVersion(QString fileName);

signals:
	void updateAvailable();
	void isUpToDate();
	void progressValueChanged(int progress);
	void progressRangeChanged(int lowerLimit, int upperLimit);
	void finishedUpdating();

private:
	void checkForDataDir();
	void getInstalledVersion();
	void checkForNewVersion();
	HttpRequest *httpRequest;
	int installedVersion;
	int currentVersion;
};

#endif /* Updater_hpp */
