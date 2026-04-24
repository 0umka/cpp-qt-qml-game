#ifndef ENEMYMODEL_H
#define ENEMYMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "enemy.h"

class EnemyModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum EnemyRoles {
        EnemyObjectRole = Qt::UserRole + 1,
        PositionRole,
        HealthRole,
        MaxHealthRole
    };
    explicit EnemyModel(QObject *parent = nullptr);
    ~EnemyModel();

    //virtual
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    //
    QList<Enemy*> enemies() const { return m_enemies; }

    void addEnemy(Enemy *enemy);
    void removeEnemy(int index);
    void clear();

signals:
    void enemyAdded(Enemy* enemy);
    void enemyRemoved(int index);

private:
    QList<Enemy*> m_enemies;
    Enemy* get(int index) const;
};


#endif // ENEMYMODEL_H
