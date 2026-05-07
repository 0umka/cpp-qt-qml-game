#include "mainwindow.h"
#include "startscreen.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    StartScreen* startScreen = new StartScreen(app);

    if (!startScreen->init()) {
        return -1;
    }

    // Когда стартовый экран сигнализирует о старте — запускаем игру
    QObject::connect(
        startScreen,
        &StartScreen::gameStartRequested,
        [&app, startScreen](WeaponEntity::WeaponType weapon) {
            startScreen->deleteLater();

            MainWindow* mainWindow = new MainWindow(app, weapon);
            if (!mainWindow->initQml()) {
                QCoreApplication::exit(-1);
                return;
            }
        }
    );

    return app.exec();
}
