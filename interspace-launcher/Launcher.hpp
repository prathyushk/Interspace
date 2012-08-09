#ifndef Launcher_hpp
#define Launcher_hpp

#include <QCoreApplication>
#include <QThread>
#include <QProcess>
#include <QString>
#include <QStringList>

class Launcher : public QObject {
  Q_OBJECT

public:
  Launcher();
  ~Launcher();
  void launch();

private slots:
  void processError(QProcess::ProcessError);

private:
  QProcess *interspaceProcess;
  QString interspaceExecutable;
  QStringList interspaceArguments;
};

#endif /* Launcher_hpp */
