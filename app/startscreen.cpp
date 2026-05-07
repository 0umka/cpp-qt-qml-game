#include "startscreen.h"
#include <QDebug>

StartScreen::StartScreen(QGuiApplication& app, QObject *parent)
    : QObject(parent)
    , m_app(app)
{
    m_engine = new QQmlApplicationEngine(this);

    QObject::connect(
        m_engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection
    );
}

StartScreen::~StartScreen()
{
}

bool StartScreen::init()
{
    m_engine->rootContext()->setContextProperty("startScreen", this);

    const QUrl url(QStringLiteral("qrc:/qml/StartScreen.qml"));
    m_engine->load(url);

    return !m_engine->rootObjects().isEmpty();
}

void StartScreen::selectWeapon(int weaponId)
{
    if (m_selectedWeapon != weaponId) {
        m_selectedWeapon = weaponId;
        emit selectedWeaponChanged();
        qDebug() << "Weapon selected:" << weaponId;
    }
}

void StartScreen::startGame()
{
    WeaponEntity::WeaponType weapon;

    switch (m_selectedWeapon) {
    case 1:
        weapon = WeaponEntity::WeaponType::Sword;
        break;
    case 0:
    default:
        weapon = WeaponEntity::WeaponType::FireStaff;
        break;
    }

    m_engine->rootObjects().first()->deleteLater();

    emit gameStartRequested(weapon);
}
