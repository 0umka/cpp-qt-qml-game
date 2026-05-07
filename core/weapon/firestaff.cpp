#include "firestaff.h"
#include <limits>

FireStaff::FireStaff(EnemyModel* enemyModel, QObject* parent) : m_enemyModel(enemyModel)
{
    m_attackTimer = new QTimer(this);
    m_attackTimer->setInterval(1000 / m_attackSpeed);
    m_attackTimer->start();
    connect(m_attackTimer, &QTimer::timeout, this, &FireStaff::attack);
}

void FireStaff::setPosition(const QPointF& pos)
{
    Q_UNUSED(pos)
}

void FireStaff::attack()
{
    if (!m_enemyModel || m_enemyModel->rowCount() == 0)
        return;

    int closestRow = -1;
    double minDistance = std::numeric_limits<double>::max();

    for (int i = 0; i < m_enemyModel->rowCount(); ++i) {
        Enemy* enemy = m_enemyModel->get(i);
        if (!enemy) continue;

        double distance = enemy->playerDistance();
        if (distance < minDistance) {
            minDistance = distance;
            closestRow  = i;
        }
    }

    if (closestRow == -1 || minDistance > m_attackRange)
        return;

    Enemy* target = m_enemyModel->get(closestRow);
    if (target) {
        target->setHealth(target->health() - m_damage);
    }
}