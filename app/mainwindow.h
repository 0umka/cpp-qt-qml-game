#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QQmlContext>

#include "entitycreator.h"

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QGuiApplication &app, QObject *parent = nullptr);

    bool initQml();

private:
    QGuiApplication& m_app;
    QQmlApplicationEngine* m_engine = nullptr;
    EntityCreator* m_playerCreator = nullptr;
    EntityCreator* m_envCreator = nullptr;
    EntityCreator* m_enemyCreator = nullptr;
};

#endif // MAINWINDOW_H
