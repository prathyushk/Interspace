#include <cstdlib>

#include <QObject>

#include "Controller.hpp"
#include "Launcher.hpp"
#include "Updater.hpp"
#include "Gui.hpp"

Controller::Controller() {
  // Initialize Members
  launcher = new Launcher();
  updater = new Updater();
  gui = new Gui();

  // Connect
  connect(this, SIGNAL(quitApp()), qApp, SLOT(quit()));
  connect(gui, SIGNAL(runLauncher()), this, SLOT(runLauncher()));

  // Show GUI
  gui->show();
}

void Controller::runLauncher() {
  gui->hide();
  launcher->launch();
  emit quitApp();
}

void Controller::runUpdater() {

}

Controller::~Controller() {
  delete launcher;
  delete updater;
  delete gui;
}
