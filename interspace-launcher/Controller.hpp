#ifndef Controller_hpp
#define Controller_hpp

#include <QObject>

#include "Launcher.hpp"
#include "Updater.hpp"
#include "Gui.hpp"

class Controller : public QObject {
  Q_OBJECT

public:
  Controller();
  ~Controller();

public slots:
  void runLauncher();
  void runUpdater();

signals:
  void quitApp();

private:
  Launcher *launcher;
  Updater *updater;
  Gui *gui;
};

#endif /* Controller_hpp */
