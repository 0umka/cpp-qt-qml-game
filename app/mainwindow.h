#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QQmlContext>
#include <QRandomGenerator>

#include "enemymodel.h"
#include "entitycreator.h"

class MainWindow : public QObject
{
    Q_OBJECT
    Q_PROPERTY(EnemyModel* enemyModel READ enemyModel CONSTANT)
    Q_PROPERTY(int enemyCount READ enemyCount)
public:
    explicit MainWindow(QGuiApplication &app, QObject *parent = nullptr);

    bool initQml();
    EnemyModel* enemyModel() const { return m_enemyModel; }
    int enemyCount() const { return m_enemyModel->rowCount(); }
    Q_INVOKABLE void spawnEnemy();

private slots:
    void updateScene();
    void setupEnemy(Enemy* enemy);
    Q_INVOKABLE void clearEnemies();

private:
    QGuiApplication& m_app;
    QQmlApplicationEngine* m_engine = nullptr;
    EntityCreator* m_playerCreator = nullptr;
    EntityCreator* m_envCreator = nullptr;
    EntityCreator* m_enemyCreator = nullptr;
    QTimer* m_gameTimer = nullptr;
    Player* m_player = nullptr;
    EnemyModel* m_enemyModel = nullptr;
    int m_enemyCounter = 0;
    void removeDeadEnemies();
};

#endif // MAINWINDOW_H
