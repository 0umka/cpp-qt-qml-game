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
    m_enemyModel = new EnemyModel(this);

    m_gameTimer = new QTimer(this);
    m_gameTimer->setInterval(16);
    m_gameTimer->start();
    connect(m_gameTimer, &QTimer::timeout, this, &MainWindow::updateScene);
}

bool MainWindow::initQml()
{
    m_engine->rootContext()->setContextProperty("game", this);
    m_engine->rootContext()->setContextProperty("enemyModel", m_enemyModel);

    m_player = static_cast<Player*>(m_playerCreator->create(m_engine));
    m_engine->rootContext()->setContextProperty("player", m_player);

    Entity* environment = m_envCreator->create(m_engine);
    m_engine->rootContext()->setContextProperty("env", environment);

    const QUrl url(QStringLiteral("qrc:/qml/MainWindow.qml"));
    m_engine->load(url);

    return !m_engine->rootObjects().isEmpty();
}

void MainWindow::spawnEnemy()
{
    Enemy* enemy = dynamic_cast<Enemy*>(m_enemyCreator->create(m_engine));

    if (!enemy) {
        delete enemy;
        return;
    }

    setupEnemy(enemy);
    m_enemyModel->addEnemy(enemy);
}

void MainWindow::clearEnemies()
{
    m_enemyModel->clear();
}

void MainWindow::removeDeadEnemies()
{
    for (int i = m_enemyModel->rowCount() - 1; i >= 0; --i) {
        Enemy* enemy = m_enemyModel->get(i);
        if (enemy && enemy->health() <= 0) {
            enemy->deleteLater();
            m_enemyModel->removeEnemy(i);
        }
    }
}
void MainWindow::updateScene()
{
    removeDeadEnemies();

    int targetCount = m_player->level();
    while (m_enemyModel->rowCount() < targetCount) {
        spawnEnemy();
    }
}

void MainWindow::setupEnemy(Enemy* enemy)
{
    qreal angle = QRandomGenerator::global()->bounded(2 * M_PI);
    qreal distance = 200 + QRandomGenerator::global()->bounded(200);
    QPointF spawnPos(
        m_player->position().x() + distance * cos(angle),
        m_player->position().y() + distance * sin(angle)
        );

    enemy->setPosition(spawnPos);
}
