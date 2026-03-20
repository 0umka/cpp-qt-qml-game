#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    MainWindow mainWindow(app);
    if (!mainWindow.initQml()) {
        return -1;
    }

    return app.exec();
}
