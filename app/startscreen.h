#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "weapon/weaponentity.h"

class StartScreen : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int selectedWeapon READ selectedWeapon NOTIFY selectedWeaponChanged)
public:
    explicit StartScreen(QGuiApplication& app, QObject *parent = nullptr);
    ~StartScreen();

    bool init();

    int selectedWeapon() const { return m_selectedWeapon; }

    Q_INVOKABLE void selectWeapon(int weaponId);
    Q_INVOKABLE void startGame();

signals:
    void selectedWeaponChanged();
    void gameStartRequested(WeaponEntity::WeaponType weapon);

private:
    QGuiApplication& m_app;
    QQmlApplicationEngine* m_engine = nullptr;
    int m_selectedWeapon = 0; // 0 = FireStaff, 1 = Sword
};

#endif // STARTSCREEN_H
