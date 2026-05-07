#include "firestaff.h"

FireStaff::FireStaff(EnemyModel *enemyModel, QObject* parent) : m_enemyModel(enemyModel)
{
    m_attackTimer->setInterval(1000 / m_attackSpeed);
    m_attackTimer->start();
    connect(m_attackTimer, &QTimer::timeout, this, &FireStaff::attack);
}

void FireStaff::setPosition(const QPointF &pos)
{

}

void FireStaff::attack()
{
    if (!m_enemyModel)
        return;

    int closestRow = -1;
    double minDistance = std::numeric_limits<double>::max();

    for (int i = 0; i < m_enemyModel->rowCount(); ++i) {
        QModelIndex index = m_enemyModel->index(i, 0);
        double distance = m_enemyModel->data(index, EnemyModel::PlayerDistanceRole).toDouble();

        if (distance < minDistance) {
            minDistance = distance;
            closestRow = i;
        }
    }

    if (closestRow == -1)
        return;

    if (minDistance <= m_attackRange) {
        QModelIndex index = m_enemyModel->index(closestRow, 0);
        int currentHealth = m_enemyModel->data(index, EnemyModel::HealthRole).toInt();
        m_enemyModel->setData(index, currentHealth - m_damage, EnemyModel::HealthRole);
    }
}
