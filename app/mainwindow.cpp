#include "mainwindow.h"

MainWindow::MainWindow(QGuiApplication& app, QObject *parent)
    : QObject{parent}
    , m_app(app)
{
    m_engine = new QQmlApplicationEngine;
    QObject::connect(
        m_engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    m_playerCreator = new PlayerCreator(this);
    m_envCreator = new EnvCreator(this);
    m_enemyCreator = new EnemyCreator(this);
}

bool MainWindow::initQml()
{
    Entity* player = m_playerCreator->create(m_engine);
    m_engine->rootContext()->setContextProperty("player", player);

    Entity* enemy = m_enemyCreator->create(m_engine);
    m_engine->rootContext()->setContextProperty("enemy", enemy);

    Entity* environment = m_envCreator->create(m_engine);
    m_engine->rootContext()->setContextProperty("env", environment);

    const QUrl url(QStringLiteral("qrc:/qml/MainWindow.qml"));
    m_engine->load(url);

    return !m_engine->rootObjects().isEmpty();
}
