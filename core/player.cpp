#include "player.h"
#include <QDebug>
#include <cmath>

Player::Player(QObject *parent)
    : EntityAlive{}
{
    m_movementTimer = new QTimer(this);
    m_movementTimer->setInterval(16);
    connect(m_movementTimer, &QTimer::timeout, this, &Player::updatePosition);
}

void Player::setHealth(int health)
{
    health = qBound(0, health, m_maxHealth);
    if (m_health != health) {
        m_health = health;
        emit healthChanged();

        if (m_health == 0) {
            emit died();
        }
    }
}

void Player::takeDamage(int damage)
{
    setHealth(m_health - damage);
    qDebug() << "Player took" << damage << "damage, health now:" << m_health;
}

void Player::onDeath()
{

}

void Player::heal(int amount)
{
    setHealth(m_health + amount);
}

void Player::setPosition(const QPointF &pos)
{
    if (m_position != pos) {
        m_position = pos;
        emit positionChanged();
    }
}

int Player::setLevel()
{

}

void Player::addExperience(int exp)
{
    m_experience += exp;
    emit experienceChanged();

    while (m_experience >= m_expPerLvl) {
        m_experience -= m_expPerLvl;
        m_level++;
        m_maxHealth += 20;
        setHealth(m_maxHealth);
        m_expPerLvl += 2 * m_level;
        emit levelChanged();
        qDebug() << "Level up! Now level" << m_level;
    }
}

void Player::startFollowingMouse()
{
    if (!m_followingMouse) {
        m_followingMouse = true;
        m_movementTimer->start();
        emit followingMouseChanged();
    }
}

void Player::setTarget(int x, int y)
{
    m_target = QPointF(x, y);
}

void Player::stopFollowingMouse()
{
    if (m_followingMouse) {
        m_followingMouse = false;
        m_movementTimer->stop();
        emit followingMouseChanged();
    }
}

void Player::updatePosition()
{
    if (m_followingMouse) {
        QPointF delta = m_target - m_position;
        float distance = std::hypot(delta.x(), delta.y());

        if (distance > m_speed) {
            QPointF currentPos = delta / distance;
            setPosition(m_position + currentPos * m_speed);
        }
    }
}
