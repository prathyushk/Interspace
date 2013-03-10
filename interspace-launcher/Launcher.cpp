#include <cstdlib>
#include <iostream>

#include <QCoreApplication>
#include <QObject>
#include <QtGui>
#include <QProcess>
#include <QString>
#include <QStringList>

#include "Launcher.hpp"

Launcher::Launcher()
{
        // Initialize Interspace Location
#ifdef PLATFORM_LINUX
        interspaceExecutable = "/bin/sh";
        interspaceArguments << QCoreApplication::applicationDirPath() + "/bin/interspace.sh";
#else
        interspaceExecutable = QCoreApplication::applicationDirPath() + "interspace.exe";
#endif

        // Initialize Interspace Process
        interspaceProcess = new QProcess();
        connect(interspaceProcess, SIGNAL(error(QProcess::ProcessError)),
                this, SLOT(processError(QProcess::ProcessError)));
}

void Launcher::launch()
{
        interspaceProcess->start(interspaceExecutable, interspaceArguments);
        interspaceProcess->waitForFinished(-1);
}

void Launcher::processError(QProcess::ProcessError error)
{
        switch (error) {
        case QProcess::FailedToStart:
                QMessageBox::information(0, "Interspace Error", "Failed to launch Interspace.");
                break;
        case QProcess::Crashed:
                QMessageBox::information(0, "Interspace Error", "Interspace has crashed.");
                break;
        case QProcess::Timedout:
                QMessageBox::information(0, "Interspace Error", "Failed to launch Interspace.");
                break;
        case QProcess::WriteError:
                QMessageBox::information(0, "Interspace Error", "Write error");
                break;
        case QProcess::ReadError:
                QMessageBox::information(0, "Interspace Error", "Read error,");
                break;
        case QProcess::UnknownError:
                QMessageBox::information(0, "Interspace Error", "An unknown error occurred.");
                break;
        default:
                QMessageBox::information(0, "Interspace Error", "An unknown error occurred.");
        }
}

Launcher::~Launcher()
{
        delete interspaceProcess;
}
