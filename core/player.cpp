#include "player.h"
#include <QDebug>
#include <cmath>

Player::Player(QObject *parent)
    : EntityAlive{}
{}

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
    m_followingMouse = true;
}

void Player::updateFollowPosition(int x, int y)
{
    if (m_followingMouse) {

        QPointF targetPos = QPointF(x, y);
        QPointF delta = targetPos - m_position;
        float distance = std::hypot(delta.x(), delta.y());

        if (distance > m_speed) {
            m_position += delta / distance;
            QPointF currentPos = delta / distance;
            setPosition(m_position + currentPos * m_speed);
        } else {
            setPosition(targetPos);
        }
    }
}

void Player::stopFollowingMouse()
{
    if (m_followingMouse) {
        m_followingMouse = false;
    }
}
