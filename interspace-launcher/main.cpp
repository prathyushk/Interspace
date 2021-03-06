#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <cstdlib>

#include <QApplication>

#include "Controller.hpp"
#include "HttpRequest.hpp"

int main(int argc, char *argv[])
{
        QApplication app(argc, argv); // Start Qt
        Controller controller; // Start Controller

        return app.exec(); // Start Update Loop
}
