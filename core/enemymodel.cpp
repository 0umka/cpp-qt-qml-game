#include "enemymodel.h"

EnemyModel::EnemyModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

EnemyModel::~EnemyModel()
{
    clear();
}

int EnemyModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_enemies.count();
}

QVariant EnemyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_enemies.count())
        return QVariant();

    Enemy* enemy = m_enemies.at(index.row());

    switch (role) {
    case EnemyObjectRole:
        return QVariant::fromValue<QObject*>(enemy);
    case PositionRole:
        return enemy->position();
    case HealthRole:
        return enemy->health();
    case MaxHealthRole:
        return enemy->maxHealth();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> EnemyModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[EnemyObjectRole] = "enemyObject";
    roles[PositionRole] = "position";
    roles[HealthRole] = "health";
    roles[MaxHealthRole] = "maxHealth";
    return roles;
}

void EnemyModel::addEnemy(Enemy* enemy)
{
    beginInsertRows(QModelIndex(), m_enemies.count(), m_enemies.count());
    m_enemies.append(enemy);
    endInsertRows();
    emit enemyAdded(enemy);
}

void EnemyModel::removeEnemy(int index)
{
    if (index < 0 || index >= m_enemies.count()) return;

    beginRemoveRows(QModelIndex(), index, index);
    Enemy* enemy = m_enemies.takeAt(index);
    enemy->deleteLater();
    endRemoveRows();
    emit enemyRemoved(index);
}

void EnemyModel::clear()
{
    if (m_enemies.isEmpty()) return;

    beginResetModel();
    for (Enemy* enemy : m_enemies) {
        enemy->deleteLater();
    }
    m_enemies.clear();
    endResetModel();
}

Enemy* EnemyModel::get(int index) const
{
    if (index < 0 || index >= m_enemies.count()) return nullptr;
    return m_enemies.at(index);
}
