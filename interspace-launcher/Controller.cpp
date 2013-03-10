#include <cstdlib>

#include <QObject>
#include <QDebug>
#include <QString>

#include "Controller.hpp"
#include "Launcher.hpp"
#include "Updater.hpp"
#include "Gui.hpp"

Controller::Controller()
{
        // Initialize Members
        launcher = new Launcher();
        updater = new Updater();
        gui = new Gui();

        // Connect
        connect(this, SIGNAL(quitApp()), qApp, SLOT(quit()));
	connect(updater, SIGNAL(updateAvailable()), gui, SLOT(updateAvailable()));
	connect(updater, SIGNAL(isUpToDate()), gui, SLOT(isUpToDate()));
	connect(updater, SIGNAL(progressValueChanged(int)), gui, SLOT(setProgressBarValue(int)));
	connect(updater, SIGNAL(progressRangeChanged(int, int)), gui, SLOT(setProgressBarRange(int, int)));
	connect(updater, SIGNAL(finishedUpdating()), gui, SLOT(finishedUpdating()));
        connect(gui, SIGNAL(runLauncher()), this, SLOT(runLauncher()));
	connect(gui, SIGNAL(runUpdater()),  this, SLOT(runUpdater()));

        // Show GUI
        gui->show();

}

Controller::~Controller()
{
        delete launcher;
        //delete updater;
        delete gui;
}

void Controller::runLauncher()
{
        gui->hide();
        launcher->launch();
        emit quitApp();
}

void Controller::runUpdater()
{

}
